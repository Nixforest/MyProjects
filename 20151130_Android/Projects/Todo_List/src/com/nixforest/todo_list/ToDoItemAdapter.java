/**
 * ToDo item adapter.
 */
package com.nixforest.todo_list;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.TextView;

/**
 * ToDo item adapter.
 * @author NguyenPT
 *
 */
public class ToDoItemAdapter extends ArrayAdapter<ToDoItem> {
	/**
	 * The resource ID for a layout file containing a TextView to use when instantiating views.
	 */
	private int resource;

	/**
	 * Constructor.
	 * @param context The current context.
	 * @param resource The resource ID for a layout file containing a TextView to use when instantiating views.
	 * @param objects The objects to represent in the ListView.
	 */
	public ToDoItemAdapter(Context context, int resource, List<ToDoItem> objects) {
		super(context, resource, objects);
		this.resource = resource;  
	}

	/**
	 * Get a View that displays the data at the specified position in the data set.
	 * @param position The position of the item within the adapter's data set of the item whose view we want.
	 * @param convertView The old view to reuse, if possible.
	 * @param parent The parent that this view will eventually be attached to.
	 * @return A View corresponding to the data at the specified position.
	 */
	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		LinearLayout todoView = null;
		ToDoItem item = getItem(position);
		String taskString = item.getTask();
		Date createdDate = item.getDateCreated();
		SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yy");
		String dateString = sdf.format(createdDate);
		if (convertView == null) {
			todoView = new LinearLayout(getContext());
			String inflater = Context.LAYOUT_INFLATER_SERVICE;
			LayoutInflater vi;
			vi = (LayoutInflater)getContext().getSystemService(inflater);
			vi.inflate(resource, todoView, true);
		} else {
			todoView = (LinearLayout)convertView;
		}
		TextView dateView = (TextView)todoView.findViewById(R.id.rowDate);
		TextView taskView = (TextView)todoView.findViewById(R.id.row);
		dateView.setText(dateString);
		taskView.setText(taskString);
		return todoView;
	}
}
