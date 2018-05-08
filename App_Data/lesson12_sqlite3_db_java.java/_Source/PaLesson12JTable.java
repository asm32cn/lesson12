// PaLesson12JTable.java

import java.awt.*;
import javax.swing.*;
import javax.swing.table.*;
import java.sql.*;
import java.util.Vector;

class PaLesson12JTable extends JTable{
	JFrame jf = new JFrame("PaLesson12JTable");

	private DefaultTableCellRenderer cellAlignCenter = new DefaultTableCellRenderer();
	private DefaultTableCellRenderer cellAlignRight = new DefaultTableCellRenderer();

	// 设置单元格不可编辑
	public boolean isCellEditable(int rowIndex, int columnIndex){
		return false;
	}

	public PaLesson12JTable(){
		jf.setTitle("PaLesson12JTable");
		jf.setSize(800, 450);
		jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jf.setLocationRelativeTo(null);

		cellAlignCenter.setHorizontalAlignment(JLabel.CENTER);
		cellAlignRight.setHorizontalAlignment(JLabel.RIGHT);

		final JScrollPane scrollPane = new JScrollPane();
		jf.getContentPane().add(scrollPane, BorderLayout.CENTER);

		setModel(getTableModel());

		final int[] columnWidth = {20, 325, 125, 45, 85, 35, 115};
		for(int i=0; i<columnWidth.length; i++){
			getColumnModel().getColumn(i).setPreferredWidth(columnWidth[i]);
		}

		scrollPane.setViewportView(this);

		getColumn("id").setCellRenderer(cellAlignRight);
		getColumn("分类ID").setCellRenderer(cellAlignCenter);
		getColumn("浏览数").setCellRenderer(cellAlignCenter);

		jf.setVisible(true);
	}

	public DefaultTableModel getTableModel(){
		final String[] columnTitles = {"id", "标题", "时间", "分类ID", "分类", "浏览数", "备注"};
		DefaultTableModel tmd = new DefaultTableModel();

		Vector columns = new Vector();
		for(int i=0; i<columnTitles.length; i++){
			columns.add(columnTitles[i]);
		}

		Connection conn = null;
		Statement stmt = null;
		Vector data = new Vector();
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
			//System.err.println( e.getClass().getName() + ": " + e.getMessage());
		}
		tmd.setDataVector(data, columns);
		return tmd;
	}

	public static void main(String[] args){
		System.out.println("Hello PaLesson12JTable.java");
		new PaLesson12JTable();
	}
}