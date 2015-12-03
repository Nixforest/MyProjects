/**
 * 
 */
package com.nixforest.todo_list;

import java.sql.Date;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteException;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

/**
 * @author NguyenPT
 * @param <MyObject>
 *
 */
public class DBAdapter {
	private static final String DATABASE_NAME = "todoList.db";
	private static final String DATABASE_TABLE = "todoItems";
	private static final int DATABASE_VERSION = 1;
	// The index (key) column name for use in where clauses
	public static final String KEY_ID = "_id";
	// The name and column index of each column in your database
	public static final String KEY_TASK = "task";
	public static final int TASK_COLUMN = 1;
	public static final String KEY_CREATION_DATE = "create_date";
	public static final int CREATION_DATE_COLUMN = 2;
	// TODO: Create public field for each column in your table
	// SQL statement to create a new database
	private static final String DATABASE_CREATE = "create table "
			+ DATABASE_TABLE + " ("
			+ KEY_ID + " integer primary key autoincrement, "
			+ KEY_TASK + " text not null, "
			+ KEY_CREATION_DATE +" long);";
	// Variable to hold the database instance
	private SQLiteDatabase db;
	// Context of the application using the database
	private final Context context;
	// Database open/upgrade helper
	private DBHelper dbHelper;
	public DBAdapter(Context _context) {
		this.context = _context;
		dbHelper = new DBHelper(this.context, DATABASE_NAME, null, DATABASE_VERSION);
	}
	public void open() throws SQLException {
		try {
			this.db = dbHelper.getWritableDatabase();
		} catch (SQLiteException ex) {
			db = dbHelper.getReadableDatabase();
		}
	}
	
	public void close() {
		this.db.close();
	}
	
	public long insertEntry(ToDoItem _myObject) {
		ContentValues contentValues = new ContentValues();
		contentValues.put(KEY_TASK, _myObject.getTask());
		 contentValues.put(KEY_CREATION_DATE, _myObject.getDateCreated().getTime());
		return db.insert(DATABASE_TABLE, null, contentValues);
	}
	public boolean removeEntry(long _rowIndex) {
		return db.delete(DATABASE_TABLE, KEY_ID + "=" + _rowIndex, null) > 0;
	}
	public Cursor getAllEntries() {
		return db.query(DATABASE_TABLE, new String[] { KEY_ID, KEY_TASK, KEY_CREATION_DATE},
				null, null, null, null, null);
	}
	public ToDoItem getEntry(long _rowIndex) throws SQLException {
		Cursor cursor = db.query(true, DATABASE_TABLE,
				new String[] {KEY_ID, KEY_TASK},
				KEY_ID + "=" + _rowIndex,
				null, null, null, null, null);
		if ((cursor.getCount() == 0) || (!cursor.moveToFirst())) {
			throw new SQLException("No to do items found for row: " + _rowIndex);
		}
		String task = cursor.getString(TASK_COLUMN);
		long created = cursor.getLong(CREATION_DATE_COLUMN);
		ToDoItem result = new ToDoItem(task, new Date(created));
		return result;
	}
	public boolean updateEntry(long _rowIndex, ToDoItem _myObject) {
		 String where = KEY_ID + "=" + _rowIndex;
		 ContentValues contentValues = new ContentValues();
		 contentValues.put(KEY_TASK, _myObject.getTask());
		 return db.update(DATABASE_TABLE, contentValues, where, null) > 0;
	}
	public Cursor setCursorToToDoItem(long _rowIndex) throws SQLException {
		Cursor result = db.query(true, DATABASE_TABLE,
				new String[] {KEY_ID, KEY_TASK},
				KEY_ID + "=" + _rowIndex,
				null, null, null, null, null);
		if ((result.getCount() == 0) || (!result.moveToFirst())) {
			throw new SQLException("No to do items found for row: " + _rowIndex);
		}
		return result;
	}
	
	private static class DBHelper extends SQLiteOpenHelper {

		public DBHelper(Context context, String name, CursorFactory factory,
				int version) {
			super(context, name, factory, version);
		}

		/**
		 * Called when no database exists in disk
		 * and the helper class needs to create a
		 * new one.
		 */
		@Override
		public void onCreate(SQLiteDatabase _db) {
			_db.execSQL(DATABASE_CREATE);
		}
		
		/**
		 * Called when there is a database version
		 * mismatch meaning that the version of the
		 * database on disk needs to be upgraded to
		 * the current version.
		 */
		@Override
		public void onUpgrade(SQLiteDatabase _db, int _oldVersion, int _newVersion) {
			// Log the version upgrade
			Log.w("TaskDBAdapter", "Upgrading from version "
					+ _oldVersion + " to "
					+ _newVersion
					+ ", which will destroy all old data");
			// Drop the old table and create a new one
			_db.execSQL("DROP TABLE IF EXISTS " + DATABASE_TABLE);
			onCreate(_db);
		}
		
	}
}
