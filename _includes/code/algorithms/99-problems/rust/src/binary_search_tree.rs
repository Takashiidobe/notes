use std::boxed::Box;

#[allow(dead_code)]
struct Node {
    value: i32,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

#[allow(dead_code)]
impl Node {
    fn new(value: i32) -> Node {
        Node {
            value,
            left: None,
            right: None,
        }
    }

    fn insert(&mut self, value: i32) {
        let new_node = Some(Box::new(Node::new(value)));
        if value < self.value {
            match self.left.as_mut() {
                None => self.left = new_node,
                Some(left) => left.insert(value),
            }
        } else {
            match self.right.as_mut() {
                None => self.right = new_node,
                Some(right) => right.insert(value),
            }
        }
    }

    fn search(&self, target: i32) -> Option<i32> {
        match self.value {
            value if target == value => Some(value),
            value if target < value => self.left.as_ref()?.search(target),
            value if target > value => self.right.as_ref()?.search(target),
            _ => None,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        let mut tree = Node::new(5);
        tree.insert(4);
        assert_eq!(Some(4), tree.search(4));
    }

    #[test]
    fn test_2() {
        let mut tree = Node::new(5);
        tree.insert(3);
        assert_eq!(None, tree.search(4));
    }
}
