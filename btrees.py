from collections import deque
import random


class BNode:
    """B-tree node"""

    def __init__(self, numkeys, leaf: bool):
        self.keys = []
        self.children = []
        self.numkeys = numkeys
        self.leaf = leaf

    def insert_key(self, key: int):
        """inserts new key to node"""
        self.keys.append(key)
        self.keys.sort()

    def __repr__(self):
        res = "".join([f"{k} " for k in self.keys])
        return f"({res})"


class BTree:
    """B-tree"""

    def __init__(self, numkeys) -> None:
        self.numkeys = numkeys
        self.root = None

    def insert(self, key) -> None:
        """inserts key into b-tree"""
        if not self.root:
            self.root = BNode(self.numkeys, True)
            self.root.insert_key(key)
            return

        def insert_down(node: BNode, key: int):
            if node.leaf:
                node.insert_key(key)
                return
            idx, child = -1, None
            for index, k in enumerate(node.keys):
                if key < k:
                    idx = index
                    break
            if idx == -1:
                idx = len(node.keys)
            child = node.children[idx]
            insert_down(child, key)

            if len(child.keys) == self.numkeys + 1:
                middle_index = self.numkeys // 2

                node.insert_key(child.keys[middle_index])

                left_child = BNode(self.numkeys, child.leaf)
                right_child = BNode(self.numkeys, child.leaf)

                left_child.keys = child.keys[:middle_index]
                right_child.keys = child.keys[middle_index + 1 :]

                left_child.children = child.children[: middle_index + 1]
                right_child.children = child.children[middle_index + 1 :]

                node.children = (
                    node.children[:idx]
                    + [left_child, right_child]
                    + node.children[idx + 1 :]
                )

        insert_down(self.root, key)

        if len(self.root.keys) == self.numkeys + 1:
            # root must be split
            middle_index = self.numkeys // 2
            new_root = BNode(self.numkeys, False)
            new_root.insert_key(self.root.keys[middle_index])

            left_child = BNode(self.numkeys, self.root.leaf)
            right_child = BNode(self.numkeys, self.root.leaf)

            left_child.keys = self.root.keys[:middle_index]
            right_child.keys = self.root.keys[middle_index + 1 :]

            left_child.children = self.root.children[: middle_index + 1]
            right_child.children = self.root.children[middle_index + 1 :]
            new_root.children = [left_child, right_child]
            self.root = new_root

    def print_tree(self, with_children=False) -> None:
        """Prints tree in a level order traversal"""
        if not self.root:
            print("Empty tree")
            return
        q = deque([self.root])

        while q:
            l = len(q)
            for _ in range(l):
                node = q[-1]
                q.pop()
                if with_children:
                    print(f"{node.keys}:{node.children}", end="  ")
                else:
                    print(f"{node.keys}", end=" ")
                for child in node.children:
                    q.appendleft(child)
            print()


if __name__ == "__main__":
    tree = BTree(3)
    nums = [x for x in range(23)]
    random.shuffle(nums)

    # nums = [20, 14, 5, 9, 21, 3, 2, 10]
    for num in nums:
        print(f"inserting: {num}")
        tree.insert(num)
        tree.print_tree()
        # print("-----------")
        # tree.print_tree(with_children=True)
        print()
