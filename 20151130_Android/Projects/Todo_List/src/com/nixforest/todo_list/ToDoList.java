/**
 * Main activity.
 */
package com.nixforest.todo_list;

import java.sql.Date;
import java.util.ArrayList;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.content.DialogInterface.OnClickListener;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.EditText;
import android.widget.ListView;

/**
 * Main activity.
 * @author NguyenPT
 */
public class ToDoList extends Activity {
	/**
	 * Text entry key.
	 */
	private static final String TEXT_ENTRY_KEY = "TEXT_ENTRY_KEY";
	/**
	 * Adding entry key.
	 */
	private static final String ADDING_ENTRY_KEY = "ADDING_ENTRY_KEY";
	/**
	 * Selected entry key.
	 */
	private static final String SELECTED_ENTRY_KEY = "SELECTED_ENTRY_KEY";
	/**
	 * Add new menu.
	 */
	static final private int	ADD_NEW_TODO		= Menu.FIRST;
	/**
	 * Remove menu.
	 */
	static final private int	REMOVE_TODO			= Menu.FIRST + 1;
	/**
	 * Variable check if in Adding new state.
	 */
	private boolean				addingNew			= false;
	/**
	 * List view control.
	 */
	private ListView 			myListView;
	/**
	 * Edit text control.
	 */
	private EditText 			myEditText;
	/**
	 * List to do items data.
	 */
	private ArrayList<ToDoItem>	todoItems;
	/**
	 * ToDoItem adapter.
	 */
	private ToDoItemAdapter		aa;
	/**
	 * Database adapter.
	 */
	private DBAdapter			todoDBAdapter;
	/**
	 * Current cursor.
	 */
	private Cursor				todoListCursor;

	/**
	 *Called when the activity is starting
	 * @param savedInstanceState If the activity is being re-initialized after
	 *                              previously being shut down then this Bundle
	 *                              contains the data it most recently supplied
	 *                              in onSaveInstanceState(Bundle).
	 *                              Note: Otherwise it is null.
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_to_do_list);
		// Get references to UI widgets
		myListView = (ListView)findViewById(R.id.myListView);
		myEditText = (EditText)findViewById(R.id.myEditText);
		todoDBAdapter = new DBAdapter(this);
		// Create the array list of to do items
		todoItems = new ArrayList<ToDoItem>();
		// Create the array adapter to bind the array to the listview
		aa = new ToDoItemAdapter(this,
				R.layout.todolist_item,
				todoItems);
		// Bind the array adapter to the listView
		myListView.setAdapter(aa);
		myEditText.setOnKeyListener(new View.OnKeyListener() {
			
			@Override
			public boolean onKey(View arg0, int arg1, KeyEvent arg2) {
				if (arg2.getAction() == KeyEvent.ACTION_DOWN) {
					if (arg1 == KeyEvent.KEYCODE_ENTER) {
						if (!myEditText.getText().toString().isEmpty()) {
							ToDoItem newItem;
							newItem = new ToDoItem(myEditText.getText().toString());
							//todoItems.add(0, newItem);
							todoDBAdapter.insertEntry(newItem);
							updateArray();
							myEditText.setText("");
							aa.notifyDataSetChanged();							
							cancelAdd();
							return true;
						} else {
							AlertDialog.Builder ad = new AlertDialog.Builder(ToDoList.this);
							ad.setTitle("Error");
							ad.setMessage("Content is empty!");
							ad.setPositiveButton("Retry",
									new OnClickListener() {
										
										@Override
										public void onClick(DialogInterface arg0, int arg1) {
											myEditText.requestFocus();
										}
									});
							ad.setNegativeButton("Stop",
									new OnClickListener() {
										
										@Override
										public void onClick(DialogInterface arg0, int arg1) {
											cancelAdd();
										}
									});
							ad.setCancelable(true);
							ad.setOnCancelListener(new OnCancelListener() {
								
								@Override
								public void onCancel(DialogInterface arg0) {
									// TODO Auto-generated method stub
									myEditText.requestFocus();
								}
							});
							ad.show();
						}
					}
				}
				return false;
			}
		});
		registerForContextMenu(myListView);
		restoreUIState();
		
		// Open or create the database
		todoDBAdapter.open();
		populateTodoList();
	}

	/**
	 * Reload list view control.
	 */
	private void updateArray() {
		todoListCursor.requery();
		todoItems.clear();
		if (todoListCursor.moveToFirst()) {
			do {
				String task = todoListCursor.getString(DBAdapter.TASK_COLUMN);
				long created = todoListCursor.getLong(DBAdapter.CREATION_DATE_COLUMN);
				ToDoItem newItem = new ToDoItem(task, new Date(created));
				todoItems.add(0, newItem);
			} while (todoListCursor.moveToNext());
		}
		aa.notifyDataSetChanged();
	}

	/**
	 * Start update list view data.
	 */
	private void populateTodoList() {
		// Get all to do list items from the database
		todoListCursor = todoDBAdapter.getAllEntries();
		startManagingCursor(todoListCursor);
		// Update the array
		updateArray();
	}

	/**
	 * Initialize the contents of the Activity's standard options menu.
	 * @param menu The options menu in which you place your items.
	 * @return true for the menu to be displayed
	 */
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		//getMenuInflater().inflate(R.menu.to_do_list, menu);
		super.onCreateOptionsMenu(menu);
		// Create and add new menu items
		MenuItem itemAdd = menu.add(0, ADD_NEW_TODO, Menu.NONE, R.string.add_new);
		MenuItem itemRem = menu.add(0, REMOVE_TODO, Menu.NONE, R.string.remove);
		// Assign icons
		itemAdd.setIcon(R.drawable.add);
		itemRem.setIcon(R.drawable.close);
		
		// Allocate shortcuts to each of them
		itemAdd.setShortcut('0', 'a');
		itemRem.setShortcut('1', 'r');
		return true;
	}

	/**
	 * This hook is called whenever an item in your options menu is selected.
	 * @param item The menu item that was selected.
	 * @return Return false to allow normal menu processing to proceed,
	 * true to consume it here.
	 */
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		//int id = item.getItemId();
		//if (id == R.id.action_settings) {
		//	return true;
		//}
		super.onOptionsItemSelected(item);
		int idx = myListView.getSelectedItemPosition();
		switch (item.getItemId()) {
			case REMOVE_TODO: {
				if (addingNew) {
					cancelAdd();
				} else {
					removeItem(idx);
				}
				return true;
			}
			case ADD_NEW_TODO: {
				addNewItem();
				return true;
			}
			default: break;
		}
		return false;
	}

	/**
	 * Cancel adding state.
	 */
	private void cancelAdd() {
		addingNew = false;
		myEditText.setVisibility(View.GONE);
	}

	/**
	 * Add new item.
	 */
	private void addNewItem() {
		addingNew = true;
		myEditText.setVisibility(View.VISIBLE);
		myEditText.requestFocus();
	}

	/**
	 * Remove item from list view.
	 * @param _index Index of item.
	 */
	private void removeItem(int _index) {
		//todoItems.remove(_index);
		//aa.notifyDataSetChanged();
		todoDBAdapter.removeEntry(todoItems.size() - _index);
		updateArray();
	}

	/**
	 * Perform any final cleanup before an activity is destroyed.
	 */
	@Override
	public void onDestroy() {
		// Close the database
		todoDBAdapter.close();
		super.onDestroy();
	}

	/**
	 * Called when a context menu for the view is about to be shown.
	 * @param menu The context menu that is being built.
	 * @param v The view for which the context menu is being built.
	 * @param menuInfo Extra information about the item for which the context menu should be shown.
	 */
	@Override
	public void onCreateContextMenu(ContextMenu menu,
			View v, ContextMenu.ContextMenuInfo menuInfo) {
		super.onCreateContextMenu(menu, v, menuInfo);
		menu.setHeaderTitle("Selected To Do Item");
		menu.add(0, REMOVE_TODO, Menu.NONE, R.string.remove);
	}

	/**
	 * Prepare the Screen's standard options menu to be displayed.
	 * @param menu The options menu as last shown or first initialized by onCreateOptionsMenu().
	 * @return You must return true for the menu to be displayed;
	 * if you return false it will not be shown.
	 */
	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {
		super.onPrepareOptionsMenu(menu);
		// Get references to UI widgets
		int idx = myListView.getSelectedItemPosition();
		String removeTitle = getString(addingNew ? R.string.cancel : R.string.remove);
		MenuItem removeItem = menu.findItem(REMOVE_TODO);
		removeItem.setTitle(removeTitle);
		removeItem.setVisible(addingNew || (idx > -1));
		return true;
	}

	/**
	 * This hook is called whenever an item in a context menu is selected.
	 * @param item The context menu item that was selected.
	 * @return Return false to allow normal context menu processing to proceed, true to consume it here.
	 */
	@Override
	public boolean onContextItemSelected(MenuItem item) {
		super.onContextItemSelected(item);
		switch (item.getItemId()) {
			case REMOVE_TODO: {
				AdapterView.AdapterContextMenuInfo menuInfo;
				menuInfo = (AdapterView.AdapterContextMenuInfo)item.getMenuInfo();
				int idx = menuInfo.position;
				removeItem(idx);
				return true;
			}
			case ADD_NEW_TODO: {
				addNewItem();
				return true;
			}
			default: break;
		}
		return false;
	}

	/**
	 * Called as part of the activity lifecycle when an activity is going
	 * into the background, but has not (yet) been killed.
	 */
	@Override
	protected void onPause() {
		super.onPause();
		// Get the activity preferences object
		SharedPreferences uiState = getPreferences(Activity.MODE_PRIVATE);
		// Get the preferences editor
		SharedPreferences.Editor edt = uiState.edit();
		// Add the UI state preferences values
		edt.putString(TEXT_ENTRY_KEY, myEditText.getText().toString());
		edt.putBoolean(ADDING_ENTRY_KEY, addingNew);
		// Commit the preferences
		edt.commit();
	}

	/**
	 * Restore UI state.
	 */
	private void restoreUIState() {
		// Get the activity preferences object
		SharedPreferences settings = getPreferences(Activity.MODE_PRIVATE);
		// Read the UI state values, specifying default values
		String text = settings.getString(TEXT_ENTRY_KEY, "");
		Boolean adding = settings.getBoolean(ADDING_ENTRY_KEY, false);
		// Restore the UI to the previous state
		if (adding) {
			addNewItem();
			myEditText.setText(text);
		}
	}

	/**
	 * Called to retrieve per-instance state from an activity before being killed.
	 * @param outState Bundle in which to place your saved state.
	 */
	@Override
	public void onSaveInstanceState(Bundle outState) {
		outState.putInt(SELECTED_ENTRY_KEY, myListView.getSelectedItemPosition());
		super.onSaveInstanceState(outState);
	}

	/**
	 * This method is called after onStart() when the activity is being re-initialized from a previously saved state.
	 * @param savedInstanceState the data most recently supplied in onSaveInstanceState(Bundle).
	 */
	@Override
	public void onRestoreInstanceState(Bundle savedInstanceState) {
		int pos = -1;
		if (savedInstanceState != null) {
			if (savedInstanceState.containsKey(SELECTED_ENTRY_KEY)) {
				pos = savedInstanceState.getInt(SELECTED_ENTRY_KEY);
			}
		}
		myListView.setSelection(pos);
	}
}
