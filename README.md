
===============================================================================

Matthew Dunfee

===============================================================================

//start with upper
Public methods (8 total):
    1. Constructor: BinarySearchTree()
    2. Destructor: ~BinarySearchTree()
    3. InOrder()
    4. PostOrder()
    5. PreOrder()
    6. Insert(Bid bid)
    7. Remove(string bidId)
    8. Search(string bidId)
    
//start with lower
Private members (7 total Helpers):
    1. Data member: Node* root
    2. Private method: addNode(Node* node, Bid bid)
    3. Private method: inOrder(Node* node)
    4. Private method: postOrder(Node* node)
    5. Private method: preOrder(Node* node)
    6. Private method: removeNode(Node* node, string bidId)
    7. Private method: destroy(Node* node)


===============================================================================
*
*
*
CLASS BinarySearchTree:
    // Private members (6 total)
    PRIVATE:
*
*
*
===============================================================================

        // 1. Data member: the root node pointer.
        VARIABLE root

===============================================================================

        // 2. Helper to recursively add a bid.
        FUNCTION addNode(current, bid):
            IF bid.key < current.bid.key:
                IF current.left IS null:
                    SET current.left TO NEW Node(bid)
                ELSE:
                    CALL addNode(current.left, bid)
            ELSE:
                IF current.right IS null:
                    SET current.right TO NEW Node(bid)
                ELSE:
                    CALL addNode(current.right, bid)

===============================================================================

        // 3. Recursive InOrder traversal helper.
        FUNCTION inOrder(node):
            IF node IS null: RETURN
            CALL inOrder(node.left)
            OUTPUT node.bid details
            CALL inOrder(node.right)

===============================================================================

        // 4. Recursive PreOrder traversal helper.
        FUNCTION preOrder(node):
            IF node IS null: RETURN
            OUTPUT node.bid details
            CALL preOrder(node.left)
            CALL preOrder(node.right)

===============================================================================

        // 5. Recursive PostOrder traversal helper.
        FUNCTION postOrder(node):
            IF node IS null: RETURN
            CALL postOrder(node.left)
            CALL postOrder(node.right)
            OUTPUT node.bid details

===============================================================================

        // 6. Helper to recursively remove a node.
        FUNCTION removeNode(node, bidId):
            IF node IS null:
                RETURN null
            IF bidId < node.bid.bidId:
                SET node.left TO removeNode(node.left, bidId)
            ELSE IF bidId > node.bid.bidId:
                SET node.right TO removeNode(node.right, bidId)
            ELSE:
                // Found the node to remove.
                // Case 1: No children.
                IF node.left IS null AND node.right IS null:
                    DELETE node
                    RETURN null
                // Case 2: One child (only right).
                ELSE IF node.left IS null:
                    SET temp TO node.right
                    DELETE node
                    RETURN temp
                // Case 2: One child (only left).
                ELSE IF node.right IS null:
                    SET temp TO node.left
                    DELETE node
                    RETURN temp
                // Case 3: Two children.
                ELSE:
                    // Find in-order successor (minimum in right subtree).
                    SET temp TO node.right
                    WHILE temp.left IS NOT null:
                        SET temp TO temp.left
                    SET node.bid TO temp.bid
                    SET node.right TO removeNode(node.right, temp.bid.bidId)
            RETURN node

===============================================================================

    // 7. Helper to recursively deallocate memory of a tree.
    FUNCTION destroy(Node* node):
        IF node IS NOT null:
            CALL destroy(node.left)
            CALL destroy(node.right)
            DELETE node
    
===============================================================================
*
*
*
    // Public methods (8 total)
    PUBLIC:
*
*
*
===============================================================================

        // 1. Constructor: Initializes the tree.
        FUNCTION BinarySearchTree():
            SET root TO null

===============================================================================

        // 2. Destructor: Frees memory for all nodes.
        FUNCTION ~BinarySearchTree():
            // Inline post-order deletion logic.
            FUNCTION destroy(node):
                IF node IS NOT null:
                    CALL destroy(node.left)
                    CALL destroy(node.right)
                    DELETE node
            CALL destroy(root)

===============================================================================

        // 3. Public InOrder traversal that calls the private helper.
        FUNCTION InOrder():
            CALL inOrder(root)

===============================================================================

        // 4. Public PreOrder traversal.
        FUNCTION PreOrder():
            CALL preOrder(root)

===============================================================================

        // 5. Public PostOrder traversal.
        FUNCTION PostOrder():
            CALL postOrder(root)

===============================================================================

        // 6. Public Insert: Adds a bid to the BST.
        FUNCTION Insert(bid):
            IF root IS null:
                SET root TO NEW Node(bid)
            ELSE:
                CALL addNode(root, bid)

===============================================================================

        // 7. Public Remove: Removes a bid by bidId.
        FUNCTION Remove(bidId):
            SET root TO removeNode(root, bidId)

===============================================================================

        // 8. Public Search: Finds and returns a bid by bidId.
        FUNCTION Search(bidId):
            SET current TO root
            WHILE current IS NOT null AND current.bid.bidId IS NOT bidId:
                IF bidId < current.bid.bidId:
                    SET current TO current.left
                ELSE:
                    SET current TO current.right
            IF current IS NOT null:
                RETURN current.bid
            ELSE:
                RETURN an empty bid (or null indicator)

===============================================================================
