/**
 * ToDoItem model class.
 */
package com.nixforest.todo_list;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * ToDoItem model class.
 * @author NguyenPT
 *
 */
public class ToDoItem {
	/**
	 * Task content.
	 */
	private	String	task;
	/**
	 * Created date information.
	 */
	private	Date	dateCreated;

	/**
	 * Constructor.
	 * @param _task Task content.
	 */
	public ToDoItem(String _task) {
		this(_task, new Date(java.lang.System.currentTimeMillis()));
	}

	/**
	 * Contructor.
	 * @param _task Task content.
	 * @param _created Created date.
	 */
	public ToDoItem(String _task, Date _created) {
		task = _task;
		dateCreated = _created;
	}

	/**
	 * Convert to string.
	 * @return String object.
	 */
	@Override
	public String toString() {
		SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yy");
		String dateString = sdf.format(dateCreated);
		return "[" + dateString + "] " + task;
	}

	/**
	 * Get task string.
	 * @return String of task.
	 */
	public String getTask() {
		return task;
	}

	/**
	 * Set task string.
	 * @param task Task content.
	 */
	public void setTask(String task) {
		this.task = task;
	}

	/**
	 * Get created date information.
	 * @return Date information.
	 */
	public Date getDateCreated() {
		return dateCreated;
	}

	/**
	 * Set created date information.
	 * @param dateCreated Created date information.
	 */
	public void setDateCreated(Date dateCreated) {
		this.dateCreated = dateCreated;
	}
}
