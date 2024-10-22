#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTextCodec>
#include <QDataStream>

void QFileTest(void)
{
    QFile file("/home/vito/Downloads/abc.txt");
    bool ok = file.open(QFile::ReadWrite);
    if (!ok) {
        qDebug() << "Fail to open abc.txt : " << file.errorString();
        return;
    }

    // qDebug() << "-------------------------";
    QFileInfo qFileInfo(file);
    qDebug() << qFileInfo.absoluteFilePath();

    // qDebug() << "-------------------------";
    file.write("hello  abc.txt");

    // qDebug() << "-------------------------";
    // 刷新缓存
    file.flush();
    // 更改文件偏移量
    file.seek(0);

    QByteArray data = file.readAll();
    qDebug() << data.size();
    qDebug() << QString(data);

    // qDebug() << "-------------------------";
    file.seek(0);

    char data1;
    while(!file.atEnd()) {
        file.read(&data1, sizeof(data1));
        qDebug() << data1;
    }

    // qDebug() << "-------------------------";
    qDebug() << qFileInfo.baseName();
    qDebug() << qFileInfo.completeBaseName();
    qDebug() << qFileInfo.suffix();
    qDebug() << qFileInfo.completeSuffix();
    qDebug() << qFileInfo.size();



    file.close();
}

void QTextStreamTest()
{
    QFile file("/home/vito/Downloads/abc.txt");
    bool ok = file.open(QFile::ReadWrite | QFile::Truncate);
    if (!ok) {
        qDebug() << "Fail to open abc.txt : " << file.errorString();
        return;
    }

    QTextStream ts(&file);
    ts << "data : " << qSetFieldWidth(10) << 123 << 3.14 << "\n";

    ts << showbase << uppercasedigits << hex << 12345678;

    // 写有可能只写到了 缓存中去了，需要刷新一下 才能读取
    ts.flush();
    file.seek(0);

    qDebug() << QTextStream(&file).readAll();

    file.close();
}

void QTextCodec()
{
    // qDebug() << QTextCodec::availableCodecs();

    QFile file("/home/vito/Downloads/abc.txt");
    bool ok = file.open(QFile::ReadOnly);
    if (!ok) {
        qDebug() << "Fail to open abc.txt : " << file.errorString();
        return;
    }

    QTextStream ts(&file);
    qDebug() << "codec ： " << ts.codec()->name();
    // ts.setCodec("gbk");
    qDebug() << ts.readAll();

    file.close();
}

//将常用类型的数据以二进制写入到制定的目标中，同时也可以按写入的顺序从目标中读取这些类型的数据，实现数据的序列化
void QDataStreamTest()
{
    QFile file("/home/vito/Downloads/abc.txt");
    bool ok = file.open(QFile::ReadWrite | QFile::Truncate);
    if (!ok) {
        qDebug() << "Fail to open abc.txt : " << file.errorString();
        return;
    }

    QDataStream ds(&file);

    ds << "tiechui";
    ds << 30;
    ds << 90.8;

    file.seek(0);

    QDataStream rs(&file);
    quint32 len = 10;
    char *name = new char[len];
    rs.readBytes(name, len);
    quint32 age;
    qreal score;
    rs >> age;
    rs >> score;

    qDebug() << "Name : " << name;
    qDebug() << "age  : " << age;
    qDebug() << "score: " << score;

    file.close();
}

/*
 * QApplication: 类它包含主事件循环， 用来处理来自窗口系统和其他资源的事件
 * MainWindow：自定义的类，创建对象w时调用MainWindow的构造函数，构造函数里面把界面上需要用到的对象进行创建，并且用MainWindow创建的对象作为他们的父对象
 * 显示MainWIndow对象，此时那些以Mainindow对象作父对象的子对象也一起显示出来
 *
 * 开启事件循环，捕获事件，如：键盘、鼠标等事件
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // QTextStreamTest();
    // QDataStreamTest();

    // 字符串拼接
    // QString str1 = "hello";
    // str1 += " world";
    // qDebug() << str1;

    // QString str1 = "Q", str2 = "T";
    // QString str3 = str1;
    // qDebug() << str1.append(str2);
    // qDebug() << str3.append(str2);

    // QString i = "123";
    // QString total = "999";
    // QString fileName = "qt";
    // QString status = QString("Processing file %1 of %2: %3")
    //                      .arg(i).arg(total).arg(fileName);
    // qDebug() << status;

    // QString str = "你好!";
    // qDebug() << str.count();
    // qDebug() << str.size();
    // qDebug() << str.length();

    // QString str1, str2 = "";
    // qDebug() << str1.isNull();
    // qDebug() << str1.isEmpty();
    // qDebug() << str2.isEmpty();

    // QString str1 = "qt";
    // bool b = str1.contains("QT", Qt::CaseInsensitive);  // 大小写不敏感
    // bool b1 = str1.contains("QT", Qt::CaseSensitive);   // 大小写敏感
    // qDebug() << b;
    // qDebug() << b1;

    // QString s = "123.2";
    // qDebug() << s.toInt();
    // qDebug() << s.toDouble();
    // double i = 123.21;
    // qDebug() << QString::number(i);
    // qDebug() << QString::number(i, 'f', 2);

    // QString str;
    // QString csv = "forename,middlename,surname,phone";
    // QString path = "/usr/local/bin/myapp";
    // QString::SectionFlag flag = QString::SectionSkipEmpty;
    // qDebug() << csv.section(',', 2, 2);
    // qDebug() << path.section('/', 3, 4);
    // qDebug() << path.section('/', 3, 3, flag);

    // QString str = "a,,b,c";
    // QStringList list1 = str.split(',');
    // qDebug() << list1;

    // QString t1 = "Ali Baba";
    // qDebug() << t1.remove(QChar('a'), Qt::CaseInsensitive);
    // QString t2 = "Ali Baba";
    // qDebug() << t2.remove("A");


    // 字节数组 byteArray
    // QByteArray ba1;
    // QByteArray ba2("abc");

    // char buf[] = {10, 20, 30};
    // QByteArray ba3(buf, sizeof(buf));

    // for(int i = 0; i < ba2.size(); i++) {
    //     qDebug() << (char)ba2[i];
    // }
    // qDebug() << "-------------------------";
    // for(int i = 0; i < ba3.count(); i++) {
    //     qDebug() << (int)ba3.at(i);
    // }
    // qDebug() << "-------------------------";
    // // 查看字节数组分配的内存大小
    // qDebug() << "ba1: " << ba1.capacity();
    // qDebug() << "ba2: " << ba2.capacity();
    // qDebug() << "ba3: " << ba3.capacity();
    // qDebug() << "-------------------------";
    // // 将字节数组转换为十六进制数据
    // QByteArray ba4 = ba3.toHex();
    // qDebug() << ba4.data();
    // QByteArray ba5 = ba3.toHex(':');
    // qDebug() << ba5.data();

    // QByteArray ba6 = QByteArray::fromHex("0a141e");
    // for(int i = 0; i < ba6.size(); i++) {
    //     qDebug() << (int)ba6[i];
    // }
    // // QString与QByteArray之间转换
    // // 1. QByteArray -> QString
    // QByteArray Data;
    // QString str = QString(Data);
    // // 2. QString -> QByteArray
    // QByteArray ba11 = str.toLatin1(); // ASCII编码
    // QByteArray ba22 = str.toLocal8Bit(); // 使用本地操作系统设置的字符集编码
    // QByteArray ba33 = str.toUtf8(); // UTF编码

    // a.exec(); 是个死循环，不会退出， 它在里面做一些事件循环，
    return a.exec();
}
