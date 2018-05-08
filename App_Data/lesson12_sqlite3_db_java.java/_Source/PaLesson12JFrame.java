// PaLesson12JFrame.java

import java.awt.*;
import javax.swing.*;
import javax.swing.table.*;
import java.sql.*;
import java.util.Vector;

class PaLesson12JFrame extends JFrame{
	private JTable table = null;
	String[][] row = new String[20][7];

	private DefaultTableCellRenderer cellAlignCenter = new DefaultTableCellRenderer();
	private DefaultTableCellRenderer cellAlignRight = new DefaultTableCellRenderer();

	public PaLesson12JFrame(){
		super("PaLesson12JFrame");
		setSize(800, 450);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);

		cellAlignCenter.setHorizontalAlignment(JLabel.CENTER);
		cellAlignRight.setHorizontalAlignment(JLabel.RIGHT);

		final JScrollPane scrollPane = new JScrollPane();
		getContentPane().add(scrollPane, BorderLayout.CENTER);

		final int[] columnWidth = {20, 325, 125, 45, 85, 35, 115};

		//DefaultTableModel tmd = getTableModel();
		table = new JTable(getTableModel());

		for(int i=0; i<columnWidth.length; i++){
			table.getColumnModel().getColumn(i).setPreferredWidth(columnWidth[i]);
		}

		scrollPane.setViewportView(table);

		table.getColumn("id").setCellRenderer(cellAlignRight);
		table.getColumn("分类ID").setCellRenderer(cellAlignCenter);
		table.getColumn("浏览数").setCellRenderer(cellAlignCenter);

		setVisible(true);
	}

	public DefaultTableModel getTableModel(){
		DefaultTableModel tmd = new DefaultTableModel();
		final String[] column = {"id", "标题", "时间", "分类ID", "分类", "浏览数", "备注"};

		tmd.setColumnIdentifiers(column);
		Vector columns = new Vector();
		for(int i=0; i<column.length; i++){
			columns.add(column[i]);
		}

		Vector data = new Vector();
		Connection conn = null;
		Statement stmt = null;
		try{
			Class.forName("org.sqlite.JDBC");
			conn = DriverManager.getConnection("jdbc:sqlite:../lesson12.sqlite3");
			//conn.setAutoCommit(false);
			stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery("select id, strTitle, strDate, nTypeID, strTypeName, nCount, strMemo from table_article");
			final String[] strKeys = {"id", "strTitle", "strDate", "nTypeID", "strTypeName", "nCount", "strMemo"};
			while(rs.next()){
				Vector v = new Vector();
				for(int i=0; i<strKeys.length; i++){
					v.add(i, rs.getString(strKeys[i]));
				}
				data.add(v);
			}
			rs.close();
			stmt.close();
			conn.close();
		}catch(Exception e){
			e.printStackTrace();
			System.err.println( e.getClass().getName() + ": " + e.getMessage());
		}
		tmd.setDataVector(data, columns);
		return tmd;
	}

	public static void main(String[] args){
		System.out.println("Hello PaLesson12JFrame.java");
		new PaLesson12JFrame();
	}
}