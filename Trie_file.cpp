#include "Trie_file.h"


void Trie::Trie_Node::make_children_fields(std::unordered_set<char> *alphabet_ptr) {
  for (const char& letter : *alphabet_ptr)
    children[letter] = nullptr;
}

std::shared_ptr<typename Trie::Trie_Node>& Trie::Trie_Node::operator[](char letter) {
  return children[letter];
}

Trie::Trie(Alphabet alphabet) {
  if (alphabet.first.size() == 0)
    throw ZERO_SIZE_ALPHABET_ERROR;
  std::reverse(alphabet.first.begin(), alphabet.first.end());
  for (const char& letter : alphabet.first)
    alphabet_.insert(letter);
  alphabet_id = alphabet.second;
  root = std::make_shared<Trie_Node>(&alphabet_);
}

Trie::~Trie() {
  root.reset();
}

bool Trie::verify_correct_alphabet_correspondence(std::string &word) {
  if (word.size() == 0)
    throw ZERO_SIZE_WORD_INPUT_ERROR;
  for (char w : word) {
    auto it = alphabet_.find(w);
    if (it == alphabet_.end())
      return false;
  }
  return true;
}

bool Trie::insert(std::string word) {
  if (verify_correct_alphabet_correspondence(word)) {
    size_t letter_counter(0);
    std::stack<std::shared_ptr<Trie_Node>> insertion_path;
    std::shared_ptr<Trie_Node> current_node = root;
    bool proceed = false;
    while (letter_counter != word.size()) {
      if (!(*current_node)[word[letter_counter]]) {
        (*current_node)[word[letter_counter]] = std::make_shared<Trie_Node>(word[letter_counter], (letter_counter + 1 == word.size()), &alphabet_);
        if(letter_counter + 1 == word.size())
          proceed = true;
      }
      else {
        if (letter_counter + 1 == word.size()) {
          (*current_node)[word[letter_counter]]->put_stamp_endword();
          proceed = true;
        }
      }
      current_node = (*current_node)[word[letter_counter]]; ++letter_counter;
      insertion_path.push(current_node);
    }
    while (proceed && !insertion_path.empty()) {
      insertion_path.top()->add_word_correspondence();
      insertion_path.pop();
    }
    return proceed;
  }
  else
    throw NON_CORRESPONDENCE_ALPHABET_ERROR;
}

bool Trie::erase(std::string word) {
  if (verify_correct_alphabet_correspondence(word)) {
    size_t letter_counter(0);
    std::stack<std::reference_wrapper<std::shared_ptr<Trie_Node>>> deletion_path;
    std::reference_wrapper<std::shared_ptr<Trie_Node>> current_node = std::ref(root);
    while ((*current_node.get())[word[letter_counter]]) {
      current_node = std::ref((*current_node.get())[word[letter_counter]]);
      if (letter_counter + 1 == word.size())
        current_node.get()->remove_stamp_endword();
      deletion_path.push(std::ref(current_node.get())), ++letter_counter;
    }
    if (letter_counter == word.size()) {
      while (!deletion_path.empty()) {
        std::reference_wrapper<std::shared_ptr<Trie_Node>> d_current_node = std::ref(deletion_path.top().get());
        deletion_path.pop();
        d_current_node.get()->subs_word_correspondence();
        if (d_current_node.get()->check_status())
          d_current_node.get().reset();
      }
      return true;
    }
    return false;
  }
  else
    throw NON_CORRESPONDENCE_ALPHABET_ERROR;
}

std::string Trie::find(std::string word) {
  if (verify_correct_alphabet_correspondence(word)) {
    size_t letter_counter(0);
    std::string word_found;
    std::shared_ptr<Trie_Node> current_node = root;
    while (letter_counter != word.size()) {
      if ((*current_node)[word[letter_counter]]) {
        word_found.push_back((*current_node)[word[letter_counter]]->get_data());
      }
      else {
        std::cout << "Given word not found." << std::endl;
        return "\0";
      }
      current_node = (*current_node)[word[letter_counter]], ++letter_counter;
    }
    if (current_node->ask_if_is_endword()) {
      std::cout << "Word found: " << word_found << std::endl;
      return word_found;
    }
    std::cout << "Given word not found." << std::endl;
    return "\0";
  }
  throw NON_CORRESPONDENCE_ALPHABET_ERROR;
  return "\0";
}