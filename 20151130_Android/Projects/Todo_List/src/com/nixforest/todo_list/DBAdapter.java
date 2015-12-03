/**
 * Database adapter.
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
 * Database adapter class.
 * @author NguyenPT
 *
 */
public class DBAdapter {
	/**
	 * Database name define.
	 */
	private static final String		DATABASE_NAME			= "todoList.db";
	/**
	 * Database table name define.
	 */
	private static final String		DATABASE_TABLE			= "todoItems";
	/**
	 * Database version number define.
	 */
	private static final int		DATABASE_VERSION		= 1;
	/**
	 * The index (key) column name for use in where clauses.
	 */
	public static final String		KEY_ID					= "_id";
	/**
	 * The name and column index of each column in your database.
	 */
	public static final String		KEY_TASK				= "task";
	/**
	 * The name of create date column in database.
	 */
	public static final String		KEY_CREATION_DATE		= "create_date";
	/**
	 * Task column number.
	 */
	public static final int 		TASK_COLUMN 			= 1;
	/**
	 * Created date column number.
	 */
	public static final int 		CREATION_DATE_COLUMN	= 2;
	/**
	 * SQL statement to create a new database.
	 */
	private static final String 	DATABASE_CREATE 		= "create table "
															+ DATABASE_TABLE + " ("
															+ KEY_ID + " integer primary key autoincrement, "
															+ KEY_TASK + " text not null, "
															+ KEY_CREATION_DATE +" long);";
	/**
	 * Variable to hold the database instance.
	 */
	private SQLiteDatabase db;
	/**
	 * Database open/upgrade helper.
	 */
	private DBHelper dbHelper;

	/**
	 * Constructor.
	 * @param _context	Context of the application using the database.
	 */
	public DBAdapter(Context _context) {
		dbHelper = new DBHelper(_context, DATABASE_NAME, null, DATABASE_VERSION);
	}

	/**
	 * Open database connection.
	 * @throws SQLException Throw when open has failed.
	 */
	public void open() throws SQLException {
		try {
			this.db = dbHelper.getWritableDatabase();
		} catch (SQLiteException ex) {
			db = dbHelper.getReadableDatabase();
		}
	}

	/**
	 * Close database connection.
	 */
	public void close() {
		this.db.close();
	}

	/**
	 * Insert an entry into database.
	 * @param _myObject Object to insert.
	 * @return The row ID of the newly inserted row, or -1 if an error occurred.
	 */
	public long insertEntry(ToDoItem _myObject) {
		ContentValues contentValues = new ContentValues();
		contentValues.put(KEY_TASK, _myObject.getTask());
		 contentValues.put(KEY_CREATION_DATE, _myObject.getDateCreated().getTime());
		return db.insert(DATABASE_TABLE, null, contentValues);
	}

	/**
	 * Remove an entry from database.
	 * @param _rowIndex The row ID of the entry to remove.
	 * @return The number of rows affected if a whereClause is passed in, 0 otherwise.
	 */
	public boolean removeEntry(long _rowIndex) {
		return db.delete(DATABASE_TABLE, KEY_ID + "=" + _rowIndex, null) > 0;
	}

	/**
	 * Get all entries from database.
	 * @return A Cursor object, which is positioned before the first entry.
	 */
	public Cursor getAllEntries() {
		return db.query(DATABASE_TABLE, new String[]{KEY_ID, KEY_TASK, KEY_CREATION_DATE},
				null, null, null, null, null);
	}

	/**
	 * Get an entry from database.
	 * @param _rowIndex The row ID of the entry to get.
	 * @return Entry value.
	 * @throws SQLException Throw exception when entry has no exist.
	 */
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

	/**
	 * Update value of an entry to database.
	 * @param _rowIndex The row ID of the entry to update.
	 * @param _myObject Object to update.
	 * @return True if update success, False otherwise.
	 */
	public boolean updateEntry(long _rowIndex, ToDoItem _myObject) {
		 String where = KEY_ID + "=" + _rowIndex;
		ContentValues contentValues = new ContentValues();
		contentValues.put(KEY_TASK, _myObject.getTask());
		 return db.update(DATABASE_TABLE, contentValues, where, null) > 0;
	}

	/**
	 * Set cursor to a specific row.
	 * @param _rowIndex The row ID of the entry to set cursor.
	 * @return A Cursor object, which is positioned before the first entry.
	 * @throws SQLException Throw exception when entry has no exist.
	 */
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

	/**
	 * Database helper class.
	 */
	private static class DBHelper extends SQLiteOpenHelper {
		/**
		 * Constructor.
		 * @param context to use to open or create the database.
		 * @param name of the database file, or null for an in-memory database.
		 * @param factory to use for creating cursor objects, or null for the default.
		 * @param version number of the database (starting at 1).
		 */
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
