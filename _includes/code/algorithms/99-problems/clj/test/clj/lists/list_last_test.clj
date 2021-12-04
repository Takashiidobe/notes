(deftest test-last-empty
  (testing "Last element of an empty array should be nil")
  (is (= (list_last []) nil)))

(deftest test-last-valid
  (testing "Last Element of [1 2 3] should be 3")
  (is (= (list_last [1 2 3]) 3)))

