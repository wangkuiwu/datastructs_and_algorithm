
#ifndef _DOUBLE_LINK_H
#define _DOUBLE_LINK_H

// 新建“双向链表”。成功，返回表头；否则，返回NULL
extern int create_dlink();
// 撤销“双向链表”。成功，返回0；否则，返回-1
extern int destroy_dlink();

// “双向链表是否为空”。为空的话返回1；否则，返回0。
extern int dlink_is_empty();
// 返回“双向链表的大小”
extern int dlink_size();

// 获取“双向链表中第index位置的元素的值”。成功，返回节点值；否则，返回-1。
extern int dlink_get(int index);
// 获取“双向链表中第1个元素的值”。成功，返回节点值；否则，返回-1。
extern int dlink_get_first();
// 获取“双向链表中最后1个元素的值”。成功，返回节点值；否则，返回-1。
extern int dlink_get_last();

// 将“value”插入到index位置。成功，返回0；否则，返回-1。
extern int dlink_insert(int index, int value);
// 将“value”插入到表头位置。成功，返回0；否则，返回-1。
extern int dlink_insert_first(int value);
// 将“value”插入到末尾位置。成功，返回0；否则，返回-1。
extern int dlink_append_last(int value);

// 删除“双向链表中index位置的节点”。成功，返回0；否则，返回-1
extern int dlink_delete(int index);
// 删除第一个节点。成功，返回0；否则，返回-1
extern int dlink_delete_first();
// 删除组后一个节点。成功，返回0；否则，返回-1
extern int dlink_delete_last();

// 打印“双向链表”
extern void print_dlink();

#endif 

