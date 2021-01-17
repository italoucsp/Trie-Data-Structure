#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Trie_DataStructure/Trie_file.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_TRIE_DataStructure {		
	TEST_CLASS(UnitTest_1_Instanciation) {
	public:
    TEST_METHOD(a_Test_case_correct_trie_building_force_error) {
      auto test_mem_function = [] {
        std::string english = "";
        Trie demo(create_alphabet(english));
      };
      Assert::ExpectException<std::out_of_range>(test_mem_function);
    }
		TEST_METHOD(b_Test_case_correct_trie_building_root_initialization) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo(create_alphabet(english));
      Assert::IsNotNull(demo.get_root().get());
		}
    TEST_METHOD(c_Test_case_get_alphabet_id) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo1(create_alphabet(english));
      std::string expected1 = "english";
      std::string russian = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
      Trie demo2(create_alphabet(russian));
      std::string expected2 = "russian";
      std::string machine = "01";
      Trie demo3(create_alphabet(machine));
      std::string expected3 = "machine";
      Assert::AreEqual(expected1, demo1.get_alphabet_id());
      Assert::AreEqual(expected2, demo2.get_alphabet_id());
      Assert::AreEqual(expected3, demo3.get_alphabet_id());
    }
	};

  TEST_CLASS(UnitTest_2_Handle_insertion) {
  public:
    TEST_METHOD(a_Test_case_insertion_error_correspondence_alphabet) {
      auto test_mem_function = [] { 
        std::string english = "abcdefghijklmnopqrstuvwxyz";
        Trie demo(create_alphabet(english));
        demo.insert("COMPUTER");
      };
      Assert::ExpectException<std::invalid_argument>(test_mem_function);
    }
    TEST_METHOD(b_Test_case_correct_single_insertion) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo(create_alphabet(english));
      Assert::AreEqual(true, demo.insert("computer"));
    }
    TEST_METHOD(c_Test_case_correct_multi_insertion) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo(create_alphabet(english));
      demo.insert("computer");
      demo.insert("science");
      demo.insert("san");
      demo.insert("pablo");
      demo.insert("university");
      std::string expected = "science";
      Assert::AreEqual(expected, demo.find("science"));
    }
    TEST_METHOD(d_Test_case_implicit_word_not_inserted) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo(create_alphabet(english));
      demo.insert("starvation");
      demo.insert("stalingrado");
      demo.insert("stars");
      demo.insert("avocado");
      std::string expected = "star";
      Assert::AreNotEqual(expected, demo.find("star"));
    }
    TEST_METHOD(e_Test_case_implicit_word_insert_after) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo(create_alphabet(english));
      demo.insert("starvation");
      demo.insert("stalingrado");
      demo.insert("stars");
      demo.insert("star");
      demo.insert("avocado");
      std::string expected = "star";
      Assert::AreEqual(expected, demo.find("star"));
    }
  };

  TEST_CLASS(UnitTest_3_Handle_deletion) {
  public:
    TEST_METHOD(a_Test_case_correct_deletion_word_exist_in_trie) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo(create_alphabet(english));
      demo.insert("apple");
      Assert::AreEqual(true, demo.erase("apple"));
    }
    TEST_METHOD(b_Test_case_correct_deletion_word_not_exist_in_trie) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo(create_alphabet(english));
      demo.insert("apple");
      Assert::AreEqual(false, demo.erase("ant"));
    }
    TEST_METHOD(c_Test_case_deletion_after_deletion) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo(create_alphabet(english));
      demo.insert("computing");
      demo.erase("computing");
      Assert::AreEqual(false, demo.erase("computing"));
    }
    TEST_METHOD(d_Test_case_correct_multi_deletion) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo(create_alphabet(english));
      demo.insert("apple");
      demo.insert("pineapple");
      demo.insert("pine");
      demo.insert("pain");
      demo.erase("pineapple");
      demo.erase("apple");
      std::string expected = "pine";
      Assert::AreEqual(expected, demo.find("pine"));
    }
    TEST_METHOD(e_Test_case_correct_multi_deletion_all) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo(create_alphabet(english));
      demo.insert("apple");
      demo.insert("pineapple");
      demo.insert("pine");
      demo.insert("pain");
      demo.erase("pineapple");
      demo.erase("pine");
      demo.erase("pain");
      demo.erase("apple");
      std::string not_expected = "pain";
      Assert::AreNotEqual(not_expected, demo.find("pain"));
    }
    TEST_METHOD(f_Test_case_insertion_post_deletion) {
      std::string english = "abcdefghijklmnopqrstuvwxyz";
      Trie demo(create_alphabet(english));
      demo.insert("apple");
      demo.insert("pineapple");
      demo.insert("dog");
      demo.erase("pineapple");
      demo.insert("pine");
      demo.insert("pain");
      std::string expected = "pine";
      Assert::AreEqual(expected, demo.find("pine"));
    }
  };
}