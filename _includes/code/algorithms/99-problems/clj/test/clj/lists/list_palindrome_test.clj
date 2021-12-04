(deftest list-palindrome-empty
  (testing "an empty list returns true")
  (is (= list_palindrome []) true))

(deftest list-palindrome-one
  (testing "a list with one item returns true")
  (is (= list_palindrome [1]) true))

(deftest list-palindrome-two
  (testing "a list with two different items returns false")
  (is (= list_palindrome [1 2]) false))
