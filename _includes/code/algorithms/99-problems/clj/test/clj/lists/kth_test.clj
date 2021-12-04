(deftest test-kth-empty
  (testing "Kth element of an empty array is nil")
  (is (= (kth []) nil)))

(deftest test-kth-out-of-bounds
  (testing "Out of bounds access is nil")
  (is (= (kth [1] 6) nil)))

(deftest test-kth-valid
  (testing "Proper access is fine")
  (is (= (kth [1 2] 1) 2)))
