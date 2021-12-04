(deftest list-reverse-test-empty
  (testing "when an empty list is reversed")
  (is (= list_reverse []) []))

(deftest list-reverse-test-one
  (testing "when a list with a single item is reversed")
  (is (= list_reverse [1]) [1]))

(deftest list-reverse-test-two
  (testing "when a list with a two items is reversed")
  (is (= list_reverse [1 2]) [2 1]))
