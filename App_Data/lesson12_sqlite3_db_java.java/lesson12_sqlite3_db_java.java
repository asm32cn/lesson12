import java.sql.*;

public class lesson12_sqlite3_db_java{
	private static String A_strQuery[] = {
		"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(9, '����٣��ۼ����˵ĳ���', '����٣��ۼ����˵ĳ���...һ������...��ӹ�ڡ��齣����¼���У�Ǭ¡�ͳ¼��������ϵĿ���...����ԭ��...�ۼ����ˣ�����٣�ǿ�����裬ǫǫ���ӣ���������...', '2016-10-24 09:43:30', 7, '��ʫ�� POEM', 0, 'Javaд��');",
		"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(10, 'SQLite(һ)����̽', 'SQLite(һ)����̽...��ǩ�� sqliteSQLiteSqlite...2013-01-23 19:12 1764���Ķ�...���ࣺ SQLite��1��...��Ȩ��������������ת�أ��鷳ע����Դ...', '2016-10-24 09:50:56', 4, 'Java', 0, 'Javaд��');",
		"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(11, 'SQLite(��): Java����SQLite', 'SQLite(��): Java����SQLite...��ǩ�� javaJavaJAVAsqliteSQLiteSqlite...2013-01-23 19:24 11976���Ķ� ����(3)...���ࣺ SQLite��1��...��Ȩ��������������ת�أ��鷳ע����Դ...', '2016-10-24 09:51:05', 4, 'Java', 0, 'Javaд��');",
		"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(12, 'SQLite - Java', '�� Java ������ʹ�� SQLite ֮ǰ��������Ҫȷ���������Ѿ��� SQLite JDBC Driver ��������� Java�����Բ鿴 Java �̳��˽�����ڼ�����ϰ�װ Java�����ڣ���������������ڻ����ϰ�װ SQLite JDBC ��������...', '2016-10-24 11:41:05', 4, 'Java', 0, 'Javaд��');"};

	public static void main(String args[]){
		Connection conn = null;
		Statement stmt = null;
		try{
			Class.forName("org.sqlite.JDBC");
			conn = DriverManager.getConnection("jdbc:sqlite:../lesson12.sqlite3");
			conn.setAutoCommit(false);
			System.out.println("Open database successfully.");

			stmt = conn.createStatement();
			int nCount = 0;
			ResultSet rs = stmt.executeQuery("select count(1) from table_article where id in (9, 10, 11, 12);");
			if (rs.next()){
				nCount = rs.getInt(1);
			}
			rs.close();

			if (nCount>0){
				System.out.println("Exists " + nCount);
			}else{
				for(int i=0; i<A_strQuery.length; i++){
					System.out.println(A_strQuery[i] + "\n");
					stmt.executeUpdate(A_strQuery[i]);
				}
			}
			stmt.executeUpdate("update table_article set nTypeID=4 where id in(10, 11, 12);");
			stmt.close();

			conn.commit();
			conn.close();
		}catch(Exception e){
			System.err.println( e.getClass().getName() + ": " + e.getMessage() );
			System.exit(0);
		}
		System.out.println("Done.");
	}
}