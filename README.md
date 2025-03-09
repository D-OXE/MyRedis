# 这是一个Redis简易版项目,立项于2025年03月09日

这个项目在初始化阶段,预计使用C++的unordered_map实现哈希表的存储.操作上类似命令行的Redis一样,以命令行的方式进行操作,预计实现持久化功能.

## 命令操作(预计实现,暂未实现)
> 下述操作均在命令行中执行,因此需要先实现一个命令行界面.
1. set key value ---> 用键值对完成对一个数据的存储(新建/修改).
2. get key ---> 获取一个键所对应的值,如果键不存在,则返回空字符串.
3. del key ---> 删除一个键所对应的值,如果键不存在,则打印错误信息.
4. expire key seconds ---> 设置一个键的过期时间,如果键不存在,则打印错误信息.
5. ttl key ---> 获取一个键的剩余过期时间,如果键不存在,则打印错误信息.
6. persist key ---> 删除一个键的过期时间,如果键不存在,则打印错误信息.
7. scan cursor [MATCH pattern] [COUNT count] ---> 扫描键,返回键的列表,如果键不存在,则返回空列表.
8. save ---> 保存本次操作的所有数据到指定文件上,如果文件不存在,则创建文件,如果文件存在,则覆盖文件. 预计将来实现追加功能
> 以上是对键值对操作的描述,对于集合,列表,哈希表等数据类型,也采用命令行的方式进行操作.

## 数据结构(预计实现,暂未实现)
1. 键值对(key,value)
2. 集合(set)
3. 列表(list)
4. 哈希表(hash)

## 后续计划,实现网络存储
1. 实现对本机端口的监听,并返回一个连接的句柄.
