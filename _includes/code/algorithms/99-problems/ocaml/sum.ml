open OUnit2

let rec sum = function
  | [] -> 0
  | h::t -> h + sum t 


let tests = "test suite for sum" >::: [
  "[]"  >:: (fun _ -> assert_equal 0 (sum []));
  "[1]"    >:: (fun _ -> assert_equal 1 (sum [1]));
  "[1;2]" >:: (fun _ -> assert_equal 3 (sum [1; 2]));
]

let run_tests = run_test_tt_main tests
