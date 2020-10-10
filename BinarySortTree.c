#include <stdio.h>
#include <malloc.h>
#include <mem.h>

#define ERROR_SUCCESS 1
#define ERROR_FALSE   0

struct BSTNode
{
    int value;
    struct BSTNode *leftTree;
    struct BSTNode *rightTree;
};

/* 前序遍历: 根-左-右 */
void preOrderTraverse(struct BSTNode *rootNode)
{
    if (NULL == rootNode)
    {
        return;
    }
    printf("%d ", rootNode->value);
    preOrderTraverse(rootNode->leftTree);
    preOrderTraverse(rootNode->rightTree);
}

/* 中序遍历: 左-根-右 */
void midOrderTraverse(struct BSTNode *rootNode)
{
    if (NULL == rootNode)
    {
        return;
    }
    midOrderTraverse(rootNode->leftTree);
    printf("%d ", rootNode->value);
    midOrderTraverse(rootNode->rightTree);
}

/* 后序遍历: 左-右-根 */
void rearOrderTraverse(struct BSTNode *rootNode)
{
    if (NULL == rootNode)
    {
        return;
    }
    rearOrderTraverse(rootNode->leftTree);
    rearOrderTraverse(rootNode->rightTree);
    printf("%d ", rootNode->value);
}


/******************************************************
 * Author : dzw
 * Date   : 2020/10/05
 * Func   : 在二叉搜索树中搜索数据
 * input  : struct BSTNode *rootNode 根节点
 *          struct BSTNode *parentNode 指向rootNode的父节点
 *          struct BSTNode **ptr 若找到，指向值为val的节点
 *                               若找不到，指向最接近val的节点
 *                               若头结点就不存在，指向NULL
 *          int val 要搜索的值
 * output : int
 ******************************************************/


int SearchBST(struct BSTNode *rootNode, struct BSTNode *parentNode,
              struct BSTNode **ptr, int val)
{
    if (NULL == rootNode) /* 根节点为空 */
    {
        *ptr = NULL;
        return ERROR_FALSE;
    }
    else if (val == rootNode->value) /* 根节点的值即为要找的值 */
    {
        *ptr = rootNode;
        return ERROR_SUCCESS;
    }
    else if (val < rootNode->value) /* 进入左子树查找 */
    {
        return SearchBST(rootNode->leftTree, rootNode, ptr, val);
    }
    else /* 进入右子树查找 */
    {
        return SearchBST(rootNode->rightTree, rootNode, ptr, val);
    }
}

/******************************************************
 * Author : dzw
 * Date   : 2020/10/05
 * Func   : 在二叉搜索树中插入数据
 * input  : struct BSTNode *rootNode 根节点
 *          int val 要插入的值
 * output : int
 ******************************************************/

int InsertBST(struct BSTNode *rootNode, int val)
{
    struct BSTNode *existNode = NULL;
    struct BSTNode *newNode = NULL;

    if (ERROR_FALSE == SearchBST(rootNode, NULL, &existNode, val)) /* 没有已存在的节点 */
    {
        newNode = (struct BSTNode *)malloc(sizeof(struct BSTNode));
        (void)memset(newNode, 0, sizeof(struct BSTNode));
        newNode->value = val;
        newNode->leftTree = NULL;
        newNode->rightTree = NULL;
        if (NULL == existNode) /* 二叉树不存在，新建一个根节点 */
        {
            rootNode = newNode;
            return ERROR_SUCCESS;
        }
        else if (val < existNode->value) /* 插入值小于最接近的值，插入为左子树 */
        {
            existNode->leftTree = newNode;
            return ERROR_SUCCESS;
        }
        else /* 插入值大于最接近的值，插入为右子树 */
        {
            existNode->rightTree = newNode;
            return ERROR_SUCCESS;
        }
    }
    else /* 插入值已存在，返回失败 */
    {
        return ERROR_FALSE;
    }
}

/******************************************************
 * Author : dzw
 * Date   : 2020/10/05
 * Func   : 在二叉搜索树中删除数据
 * input  : struct BSTNode *rootNode 根节点
 *          int val 要删除的值
 * output : int
 * （1）要删除的值在叶子节点：
 *      直接删除即可；
 * （2）要删除的值所在的节点，有一个左子树或者右子树：
 *      删除节点，并将左子树/右子树移到原先节点的位置；
 * （3）要删除的值所在的节点，既有左子树又有右子树：
 *      找到节点的直接前驱或者直接后驱，用直接前/后驱代替删除的节点；
 *      对于直接前/后驱的子树，则按照第（2）种情况处理；
 *      PS:直接前/后驱不会既有左子树又有右子树，这是二叉排序树的性质决定的；
 ******************************************************/
int DeleteNode(struct BSTNode *rootNode)
{
    struct BSTNode *tmpNode, *lt;
    if ((rootNode->leftTree == NULL)
     && (rootNode->rightTree == NULL)) /* 叶子节点 */
    {
        free(rootNode);
        rootNode = NULL;
    }
    else if ((rootNode->leftTree != NULL)
          && (rootNode->rightTree == NULL)) /* 只有左子树 */
    {
        tmpNode = rootNode;
        rootNode  = tmpNode->leftTree;
        free(tmpNode);
        tmpNode = NULL;
    }
    else if ((rootNode->leftTree == NULL)
          && (rootNode->rightTree != NULL)) /* 只有右子树 */
    {
        tmpNode = rootNode;
        rootNode  = tmpNode->rightTree;
        free(tmpNode);
        tmpNode = NULL;
    }
    else /* 左右子树都有 */
    {
        lt = rootNode->leftTree;
        tmpNode = lt;
        while (lt->rightTree != NULL)
        {
            tmpNode = lt; /* 找到直接前驱 */
            lt = lt->rightTree;
        }
        rootNode->value = lt->value;
        if (tmpNode != rootNode)
        {
            tmpNode->rightTree = lt->leftTree;
        }
        else
        {
            tmpNode->leftTree = lt->leftTree;
        }
        free(lt);
        lt = NULL;
    }
    return ERROR_SUCCESS;
}


 int DeleteBST(struct BSTNode *rootNode, int val)
{
    if (NULL == rootNode)
    {
        return ERROR_FALSE;
    }
    else
    {
        if (rootNode->value == val)
        {
            return DeleteNode(rootNode);
        }
        else if (val < rootNode->value)
        {
            return DeleteBST(rootNode->leftTree, val);
        }
        else
        {
            return DeleteBST(rootNode->rightTree, val);
        }
    }
}
