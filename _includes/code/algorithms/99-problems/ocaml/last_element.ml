open OUnit2

let rec last l = match l with
  | [] -> failwith "List is Empty"
  | [h] -> h
  | _::t -> last t

let tests = "test suite for last" >::: [
  "[1;2] 2"       >:: (fun _ -> assert_equal 2 last [1; 2]);
  "[] None" >:: (fun _ -> assert_equal Failure "List is Empty" last []);
]

let run_tests = run_test_tt_main tests

