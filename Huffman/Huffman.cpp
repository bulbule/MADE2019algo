#include "Huffman.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>
#include <string>
#include <fstream>


struct Node {
  Node(): left(nullptr), right(nullptr), freq(0), code("") {}
  unsigned char symbol;
  std::string code;
  int freq;
  Node* left;
  Node* right;
  bool operator==(const Node& other) const {
     return (symbol == other.symbol && \
             freq == other.freq && \
             code == other.code && \
             left == other.left && \
             right == other.right);
     }
};

class Huffman {
   public:
    explicit Huffman(bool encode_) {
      encode = encode_;  // used for en/decoding
      for (int i = 0; i < 256; ++i) {
        nodes[i] = new Node;
        nodes[i]->symbol = (unsigned char)i;
      }
      input_chars.clear();  // to use multiple times
      output_chars.clear();
    };
    ~Huffman();
    void build_freq_heap();
    void build_tree();
    void get_codes();
    void save_encoded_data();
    void decode_encoding_tree();
    void save_decoded_data();
    void write_byte(unsigned char);
    std::vector<unsigned char> get_output();
   
   private:
    // since we encode chars there are 256 symbols
    Node* nodes[256];
    Node* root;
    bool encode = true;
    // comparator required to build a heap
    struct cmp {
       bool operator()(Node* const& node1, Node* const& node2) const {
            return node1->freq > node2->freq;
        }
    };
    // heap based on frequences
    std::priority_queue<Node*, std::vector<Node*>, cmp> freqs_heap;
    // build part of Huffman tree from the symbol and its code("path")
    void restore_tree(std::string&, unsigned char);
    // switch to a string of binary representation
    std::string ch_to_bin_str(unsigned char);
    // input_chars = either input data to be encoded or data to be decoded
    std::vector<unsigned char> input_chars;
    std::vector<unsigned char> output_chars;
};

Huffman::~Huffman() {
    if (!root) {
        for (int i = 0; i < 256; ++i) {
            if (nodes[i]) delete nodes[i];
        }
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current_node = q.front();
        q.pop();
        if (current_node->left) {
            q.push(current_node->left);
        }
        if (current_node->right) {
            q.push(current_node->right);
        }
        delete current_node;
    }
}

void Huffman::write_byte(unsigned char ch) {
    if (encode) {
        nodes[ch]->freq++;
    }
    input_chars.push_back(ch);
}

void Huffman::build_freq_heap() {
    for (int i = 0; i < 256; ++i) {
        if (nodes[i]->freq) {
          freqs_heap.push(nodes[i]);
        }
    }
}

void Huffman::build_tree() {
    std::priority_queue<Node*, std::vector<Node*>, cmp> heap(freqs_heap);
    while (heap.size() > 1) {
        root = new Node;
        root->left  = heap.top();
        root->freq += heap.top()->freq;
        heap.pop();
        root->right = heap.top();
        root->freq += heap.top()->freq;
        heap.pop();
        heap.push(root);
    }
}

// traverse tree and build codes for symbols
void Huffman::get_codes() {
    std::stack<Node*> nodes_stack;
    nodes_stack.push(root);
    while (!nodes_stack.empty()) {
        Node* top_node = nodes_stack.top();
        nodes_stack.pop();
        if (top_node->right) {
            Node* right_node = top_node->right;
            right_node->code = top_node->code + '1';
            nodes_stack.push(right_node);
        }
        if (top_node->left) {
            Node* left_node = top_node->left;
            left_node->code = top_node->code + '0';
            nodes_stack.push(left_node);
        }
    }
}

// the format for saving is the following
// num of leaves, symbol, 00..01, code, ..,encoded data, used bits in last byte
// so the total code for each symbol is 0..01, code from tree, where the total size
// corresponds to number of leaves rounded to integer number of bytes
void Huffman::save_encoded_data() {
    std::string output_str(""), accumulator("");
    unsigned char size = freqs_heap.size();
    output_str += size;
    int bits = size + 8 - size % 8;
    // save the header
    std::priority_queue<Node*, std::vector<Node*>, cmp> heap(freqs_heap);
    while (!heap.empty()) {
        Node* current = heap.top();
        output_str += current->symbol;
        accumulator.assign(bits - 1 - current->code.size(), '0');
        accumulator += '1';
        accumulator.append(current->code);
        for (int i = 1; i <= bits / 8; i++) {
            output_str += (unsigned char)std::stoi(
                accumulator.substr(0, 8), nullptr, 2);
            accumulator = accumulator.substr(8);
        }
        heap.pop();
    }
    accumulator.clear();
    // save the encoded data itself
    for (int i = 0; i < input_chars.size(); ++i) {
        accumulator += nodes[input_chars[i]]->code;
        while (accumulator.size() > 8) {
            output_str += (unsigned char)std::stoi(
                accumulator.substr(0, 8), nullptr, 2);
            accumulator = accumulator.substr(8);
        }
    }
    // completing the last byte with zeros if necessary
    int remaining_bits = 8 - accumulator.size();
    if (remaining_bits > 0) {
        accumulator.append(remaining_bits, '0');
    }
    // store what is remained and save the amount of additional zero bits
    output_str += (unsigned char)std::stoi(accumulator, nullptr, 2);
    output_str += (unsigned char)remaining_bits;
    output_chars.clear();
    output_chars.assign(output_str.begin(), output_str.end());
}

// decoding block
void Huffman::restore_tree(std::string& path, unsigned char symbol) {
    Node* current_node = root;
    for (char& step : path) {
        if (step == '0') {
            if (!current_node->left) current_node->left = new Node;
            current_node = current_node->left;
        } else if (step == '1') {
            if (!current_node->right) current_node->right = new Node;
            current_node = current_node->right;										 
        }
    }
    current_node->symbol = symbol;
}

std::string Huffman::ch_to_bin_str(unsigned char ch) {
    return std::bitset<8>(ch).to_string();
}

// size + symbol + 0000 + 1 + code + ...
void Huffman::decode_encoding_tree() {
    unsigned char size = input_chars[0];
    int bytes = (size + 8 - size % 8) / 8;
    root = new Node;
    for (int i = 0; i < size; ++i) {
        unsigned char symbol;
        unsigned char raw_code[bytes];
        std::string final_code = "";
        symbol = input_chars[1 + (bytes + 1) * i];
        for(int j = 1; j <= bytes; ++j)
            raw_code[j - 1] = input_chars[1 + (bytes + 1) * i + j];
        for (int k = 0; k < bytes; ++k)
            final_code += ch_to_bin_str(raw_code[k]);
        int last_zero_ind = 0;
        while (final_code[last_zero_ind] == '0')
            last_zero_ind++;
        final_code = final_code.substr(last_zero_ind + 1);
        restore_tree(final_code, symbol);
    }
}

void Huffman::save_decoded_data() {
    output_chars.clear();
    unsigned char size = input_chars[0];    
    int bytes = (size + 8 - size % 8) / 8;
    unsigned char empty_bits = 8 - input_chars.back();
    std::vector<unsigned char> decoded_data;
    for (int i = 1 + (bytes + 1) * (int)size; i < input_chars.size() - 1; ++i) {
        decoded_data.push_back(input_chars[i]);
    }
    Node* current_node = root;
    std::string path;
    for (int i = 0; i < decoded_data.size(); ++i) {
        path = ch_to_bin_str(decoded_data[i]);
        if (i == decoded_data.size() - 1) path = path.substr(0, empty_bits);
        for (int j = 0; j < path.size(); j++) {
            if (path[j] == '0') {
               current_node = current_node->left;
            } else {
               current_node = current_node->right;
            }
            if (!current_node->left && !current_node->right) {
                output_chars.push_back(current_node->symbol);
                current_node = root;
            }
        }
    }
}

std::vector<unsigned char> Huffman::get_output() {
    return output_chars;
}

///////////////////////////////////////////////////////

using byte = unsigned char;

void Encode(IInputStream& original, IOutputStream& compressed) {
    byte chunk;
    Huffman encoder(true);
    while (original.Read(chunk)) {
        encoder.write_byte(chunk);
    }
    encoder.build_freq_heap();
    encoder.build_tree();
    encoder.get_codes();
    encoder.save_encoded_data();
    vector<unsigned char> encoded_data = std::move(encoder.get_output());
    for (int i = 0; i < encoded_data.size(); ++i)
        compressed.Write(encoded_data[i]);
}

void Decode(IInputStream& compressed, IOutputStream& original) {
    byte chunk;
    Huffman decoder(false);
    while (compressed.Read(chunk)) {
        decoder.write_byte(chunk);
    }
    decoder.decode_encoding_tree();
    decoder.save_decoded_data();
    vector<unsigned char> decoded_data = std::move(decoder.get_output());
    for (int i = 0; i < decoded_data.size(); ++i) {
       original.Write(decoded_data[i]);
    }
}
