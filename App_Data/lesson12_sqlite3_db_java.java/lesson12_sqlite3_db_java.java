import java.sql.*;

public class lesson12_sqlite3_db_java{
	private static String A_strQuery[] = {
		"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(9, '情深不寿，慧极必伤的出处', '情深不寿，慧极必伤的出处...一、出处...金庸在《书剑恩仇录》中，乾隆送陈家洛佩玉上的刻字...二、原句...慧极必伤，情深不寿，强极则辱，谦谦君子，温润如玉...', '2016-10-24 09:43:30', 7, '古诗词 POEM', 0, 'Java写入');",
		"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(10, 'SQLite(一)：初探', 'SQLite(一)：初探...标签： sqliteSQLiteSqlite...2013-01-23 19:12 1764人阅读...分类： SQLite（1）...版权声明：博主允许转载，麻烦注明来源...', '2016-10-24 09:50:56', 4, 'Java', 0, 'Java写入');",
		"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(11, 'SQLite(二): Java操作SQLite', 'SQLite(二): Java操作SQLite...标签： javaJavaJAVAsqliteSQLiteSqlite...2013-01-23 19:24 11976人阅读 评论(3)...分类： SQLite（1）...版权声明：博主允许转载，麻烦注明来源...', '2016-10-24 09:51:05', 4, 'Java', 0, 'Java写入');",
		"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(12, 'SQLite - Java', '在 Java 程序中使用 SQLite 之前，我们需要确保机器上已经有 SQLite JDBC Driver 驱动程序和 Java。可以查看 Java 教程了解如何在计算机上安装 Java。现在，我们来看看如何在机器上安装 SQLite JDBC 驱动程序...', '2016-10-24 11:41:05', 4, 'Java', 0, 'Java写入');"};

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