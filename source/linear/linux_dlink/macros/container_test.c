#include <stdio.h>
#include <string.h>

// 获得结构体(TYPE)的变量成员(MEMBER)在此结构体中的偏移量。
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

// 根据"结构体(type)变量"中的"域成员变量(member)的指针(ptr)"来获取指向整个结构体变量的指针
#define container_of(ptr, type, member) ({          \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

struct student
{
	char gender;
	int id;
	int age;
	char name[20];
};

void main()
{
	struct student stu;
	struct student *pstu;

	stu.gender = '1';
	stu.id = 9527;
	stu.age = 24;
	strcpy(stu.name, "zhouxingxing");

	// 根据"id地址" 获取 "结构体的地址"。
	pstu = container_of(&stu.id, struct student, id);

	// 根据获取到的结构体student的地址，访问其它成员
	printf("gender= %c\n", pstu->gender);
	printf("age= %d\n", pstu->age);
	printf("name= %s\n", pstu->name);
}
