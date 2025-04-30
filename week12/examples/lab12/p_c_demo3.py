import copy

class Parent:
    def __init__(self, i=0, n="null"):
        print("calling Parent default constructor Parent()")
        self.id = i
        self.name = n  # Python 字符串不可变，无需手动内存管理

    def __deepcopy__(self, memo):
        print("calling Parent copy constructor Parent(const Parent&)")
        new_obj = self.__class__(self.id, self.name)
        memo[id(self)] = new_obj
        return new_obj

    def assign(self, other):
        print("call Parent assignment operator:")
        if self is other:
            return self
        self.id = other.id
        self.name = other.name
        return self

    def __del__(self):
        print("call Parent destructor.")  # 实际无需手动释放资源

    def __str__(self):
        return f"Parent:{self.id}, {self.name}\n"

class Child(Parent):
    def __init__(self, i=0, n="null", s="null", a=0):
        super().__init__(i, n)
        print("call Child default constructor Child()")
        self.style = s
        self.age = a

    def __deepcopy__(self, memo):
        print("calling Child copy constructor Child(const Child&)")
        new_obj = self.__class__(self.id, self.name, self.style, self.age)
        memo[id(self)] = new_obj
        return new_obj

    def assign(self, other):
        print("call Child assignment operator:")
        if self is other:
            return self
        super().assign(other)
        self.style = other.style
        self.age = other.age
        return self

    def __del__(self):
        super().__del__()
        print("call Child destructor.")  # 父类 __del__ 会自动调用

    def __str__(self):
        #parent_str = super().__str__().replace("Parent:", "Child:", 1)
        parent_str = super().__str__()
        return f"{parent_str}Child:{self.style}, {self.age}\n"

if __name__ == "__main__":
    # 模拟 C++ 对象构造
    p1 = Parent()
    print("value in p1\n", p1)

    p2 = Parent(101, "Liming")
    print("value in p2\n", p2)

    p3 = copy.deepcopy(p1)
    print("value in p3\n", p3)

    p1.assign(p2)
    print("value in p1\n", p1)

    # 子类测试
    c1 = Child()
    print("value in c1\n", c1)

    c2 = Child(201, "Wuhong", "teenager", 15)
    print("value in c2\n", c2)

    c3 = copy.deepcopy(c1)
    print("value in c3\n", c3)

    c1.assign(c2)
    print("value in c1\n", c1)

    # 手动触发析构（Python 垃圾回收时机不确定）
    del  c3, c2, c1, p3, p2, p1

