/**
 * 
 */
package com.nixforest.todo_list;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * @author NguyenPT
 *
 */
public class ToDoItem {
	private	String	task;
	private	Date	dateCreated;
	public ToDoItem(String _task) {
		this(_task, new Date(java.lang.System.currentTimeMillis()));
	}
	public ToDoItem(String _task, Date _created) {
		task = _task;
		dateCreated = _created;
	}
	@Override
	public String toString() {
		SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yy");
		String dateString = sdf.format(dateCreated);
		return "[" + dateString + "] " + task;
	}
	public String getTask() {
		return task;
	}
	public void setTask(String task) {
		this.task = task;
	}
	public Date getDateCreated() {
		return dateCreated;
	}
	public void setDateCreated(Date dateCreated) {
		this.dateCreated = dateCreated;
	}
}
