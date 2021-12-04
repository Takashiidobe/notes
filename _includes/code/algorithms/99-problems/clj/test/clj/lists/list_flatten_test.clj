(deftest list-flatten-empty
  (testing "with an empty list")
  (is (= list_flatten []) []))

(deftest list-flatten-one-level
  (testing "with a one level list")
  (is (= list_flatten [1 2 3]) [1 2 3]))

(deftest list-flatten-two-levels
  (testing "with a two level list")
  (is (= list_flatten [1 2 3 [4 5]]) [1 2 3 4 5]))

(deftest list-flatten-many
  (testing "with many levels")
  (is (= list_flatten [1 2 3 [4 [5]]]) [1 2 3 4 5]))
