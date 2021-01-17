#pragma once
#pragma warning( disable : 4267 )

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#define get_varname(x) #x

#define ZERO_SIZE_ALPHABET_ERROR std::out_of_range("The given alphabet has a size of 0.") 
#define ZERO_SIZE_WORD_INPUT_ERROR std::out_of_range("The given word has a size of 0.") 
#define NON_CORRESPONDENCE_ALPHABET_ERROR std::invalid_argument("The given word has one or more letters there isn't in the alphabet.")

typedef std::pair<std::string, std::string> Alphabet;

#define create_alphabet(str) std::make_pair(str, get_varname(str))

class Trie {
  struct Trie_Node {
    Trie_Node() : is_endword_(true) {}
    Trie_Node(std::unordered_set<char> *alphabet_ptr)
            : is_endword_(true) { make_children_fields(alphabet_ptr); }
    Trie_Node(char const& data, bool is_endword, std::unordered_set<char> *alphabet_ptr)
            : data_(data), is_endword_(is_endword) { make_children_fields(alphabet_ptr); }
    char get_data() { return data_; }
    void add_word_correspondence() { ++n_words_using_this_node; }
    void subs_word_correspondence() { --n_words_using_this_node; }
    bool ask_if_is_endword() { return is_endword_; }
    bool check_status() { return !(n_words_using_this_node > 0); }
    void make_children_fields(std::unordered_set<char> *alphabet_ptr);
    void put_stamp_endword() { is_endword_ = true; }
    void remove_stamp_endword() { is_endword_ = false; }
    std::shared_ptr<Trie_Node>& operator[](char letter);

  private:
    char data_;
    bool is_endword_;
    size_t n_words_using_this_node = size_t(0);
    std::unordered_map<char, std::shared_ptr<Trie_Node>> children;
  };
  std::shared_ptr<Trie_Node> root;
  std::unordered_set<char> alphabet_;
  std::string alphabet_id;
  bool verify_correct_alphabet_correspondence(std::string &word);
public:
  Trie(Alphabet alphabet);
  virtual ~Trie();

  std::shared_ptr<Trie_Node> get_root() { return root; }
  bool insert(std::string word);
  bool erase(std::string word);
  std::string find(std::string word);

  std::string get_alphabet_id() { return alphabet_id; }
};

