//@ts-ignore
import { assertEquals } from "https://deno.land/std@0.68.0/testing/asserts.ts";

function twoSum(nums: number[], target: number): number[] {
  //@ts-ignore
  const map: Map<number, number> = new Map();
  let result: number[] = [-1, -1];

  for (let i = 0; i < nums.length; i++) {
    const current = nums[i];
    const match = map.get(target - current);

    if (match !== undefined) {
      result = [i, match].sort();
      break;
    }
    map.set(current, i);
  }

  return result;
}

//@ts-ignore
Deno.test("Test 1", () => {
  assertEquals(twoSum([2, 7, 11, 15], 9), [0, 1]);
});

//@ts-ignore
Deno.test("Test 2", () => {
  assertEquals(twoSum([3, 2, 4], 6), [1, 2]);
});

//@ts-ignore
Deno.test("Test 3", () => {
  assertEquals(twoSum([3, 3], 6), [0, 1]);
});

//@ts-ignore
Deno.test("Test 4", () => {
  assertEquals(twoSum([], 6), [-1, -1]);
});
