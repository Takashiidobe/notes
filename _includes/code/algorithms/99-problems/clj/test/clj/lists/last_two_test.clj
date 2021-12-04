(deftest test-last-two-empty
  (testing "Last two elements of [] should be nil")
  (is (= (last_two []) nil)))

(deftest test-last-one
  (testing "Last two elements of [1] should be [1]")
  (is (= (last_two [1]) [1])))

(deftest test-last-two
  (testing "Last two elements of [1 2 3] should be [2 3]")
  (is (= (last_two [1 2 3]) [2 3])))

