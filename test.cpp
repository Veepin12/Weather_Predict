#include <iostream>
#include <mysql/mysql.h>

using namespace std;

int main() {

MYSQL *conn;

conn = mysql_init(NULL);

if(!mysql_real_connect(conn,"localhost","root","virat","weatherdb",0,NULL,0))
{
cout<<"Connection Failed\n";
}
else
{
cout<<"Database Connected\n";
}

mysql_close(conn);

}