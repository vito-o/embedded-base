/*
核心思想：
1.开闭原则
2.里氏替换原则
3.依赖倒置原则
4.单一职责原则
5.接口隔离原则
6.迪米特法则
7.合成复用员则


1.开闭原则
    对扩展开放，对修改关闭，降低维护带来的新风险

2.里氏替换原则
    继承必须确保超类所拥有的性质在子类中仍然成立
    任何基类可以出现的地方，子类一定可以出现，只有当派生类可以替换调基类，软件功能不受影响时，基类才能真正被复用，而派生类也能够在基类的基础上增加新的行为。
    父类引用子类对象

3.依赖倒置原则
    高层模块不应该依赖低层模块，两者都应该依赖其抽象；抽象不应该依赖细节，细节应该依赖抽象
    高层不应该依赖低层，要面向接口编成。在高层和底层之间插入一层抽象层，屏蔽底层细节，向上层提供统一接口

4.单一职责原则
    一个类应该有且只有一个引起它变化的原因，否则类应该被拆分
    一个类只干一件事，实现类要单一

5.接口隔离原则
    客户端不应该被迫依赖于他不使用的方法
    一个类对另一个类的依赖应该建立在最小的接口上
    一个接口只干一件事，接口要精简单一
    要求工程师尽量将臃肿庞大的接口拆分成更小的和更具体的接口，让接口中只包含客户端感兴趣的方法。

6.迪米特法则
    最少知识原则
    不该知道的不要知道，一个类应该保持对其他对象最少的了解，降低耦合度

7.合成复用员则
    又叫，组合/聚合复用原则
    要尽量先使用组合或者聚合等关联关系来实现，其次才考虑使用继承关系来实现
    尽量使用组合或聚合关系实现代码复用，少使用继承

*/