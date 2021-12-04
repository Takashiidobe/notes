(deftest list-length-test-0
  (testing "with an empty list")
  (is (= (list_length []) 0)))

(deftest list-length-test-1
  (testing "with a list of length 1")
  (is (= (list_length [1]) 1)))

(deftest list-length-test-2
  (testing "with a list of length 2")
  (is (= (list_length [1 2]) 2)))
