open OUnit2

let rec linear_search arr t = match arr with 
  | [] -> false 
  | x::_ when x = t -> true 
  | _::xs -> linear_search xs t


let tests = "test suite for linear_search" >::: [
  "[] 10"   >:: (fun _ -> assert_equal false (linear_search [] 10));
  "[1] 1"   >:: (fun _ -> assert_equal true (linear_search [1] 1));
  "[1;2] 3" >:: (fun _ -> assert_equal false (linear_search [1; 2] 3));
  "[1;2] 4" >:: (fun _ -> assert_equal false (linear_search [1; 2] 4));
]

let run_tests = run_test_tt_main tests
