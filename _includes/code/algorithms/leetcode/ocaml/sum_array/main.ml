open OUnit2

let rec sum = function
  | [] -> 0
  | x::xs -> x + sum xs


let tests = "test suite for sum" >::: [
  "[]"  >:: (fun _ -> assert_equal 0 (sum []));
  "[1]"    >:: (fun _ -> assert_equal 1 (sum [1]));
  "[1;2]" >:: (fun _ -> assert_equal 3 (sum [1; 2]));
]

let _ = run_test_tt_main tests
