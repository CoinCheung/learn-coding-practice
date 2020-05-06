#include<iostream>
#include<string>
#include<pugixml.hpp>


using std::cout;
using std::endl;

void readPrintXml()
{
    using namespace pugi;

    cout << "in readPrintXml" << endl;

    const char* xmlfile = "./DSM.arxml"; 
    xml_document doc;

    xml_parse_result xmlparse = doc.load_file(xmlfile);
    if(xmlparse.status != status_ok)
    {

        cout << "read xml fail" << endl;
        return;
    }

    xml_node root = doc.root().first_child().first_child().first_child();
    root = root.first_child();
    cout << root.name() << endl;
    cout << root.next_sibling().name() << endl;

    std::string s = root.name();
    cout << s << endl;

    auto node = root.parent();
    cout << node.name() << endl;
    cout << node.attribute("UUID").name() << endl;
    s = node.attribute("UUID").value();
    cout << s << endl;
    cout << node.attribute("UUID");
    
    auto children = node.children();
    for(auto c:children)
        cout << c.name() << endl;

    cout << "hre" << endl;;

    auto att = node.first_attribute();

    std::string str = root.text().as_string();
    cout << str << endl;
    str = root.value();
    cout << str << endl;
    str = root.name();
    cout << str << endl;
    for(auto attr:root.attributes())
    {
        cout << attr.name() << endl;
        cout << attr.value() << endl;
    }
}


int main(void)
{
    cout << "in main" << endl;
    readPrintXml();

    return 0;
}
