(deftest remove-consecutive-duplicates
  (testing "with no duplicates")
  (is (= remove_consecutive_duplicates [1 2]) [1 2]))

(deftest remove-consecutive-duplicates-empty
  (testing "with no list")
  (is (= remove_consecutive_duplicates []) []))
