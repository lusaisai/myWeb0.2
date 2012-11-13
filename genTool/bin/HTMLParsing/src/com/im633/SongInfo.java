package com.im633;

/**
 * This class represents a song from xiami.com which supports all the music of my web site.
 */

public class SongInfo {
	private long songID;
	private String title;
	private String lyric;
	private String album;
	private String artist;
	private final String DELIMITER = "\007";
	
	public SongInfo() {
		this(-1, "", "", "", "");
	}
	
	public SongInfo(long songID, String title, String lyric, String album, String artist) {
		this.songID = songID;
		this.title = title;
		this.lyric = lyric;
		this.album = album;
		this.artist = artist;
	}
	
	public void setSongID(long songID) {
		this.songID = songID;
	}
	
	public void setTitle(String title) {
		this.title = title;
	}
	
	public void setLyric(String lyric) {
		this.lyric = lyric;
	}
	
	public void setAlbum(String album) {
		this.album = album;
	}
	
	public void setArtist(String artist) {
		this.artist = artist;
	}
	
	public long getSongID() {
		return songID;
	}
	
	public String getTitle() {
		return title;
	}
	
	public String getLyric() {
		return lyric;
	}
	
	public String getAlbum() {
		return album;
	}
	
	public String getArtist() {
		return artist;
	}
	
	public String toString() {
		return songID + DELIMITER + title + DELIMITER + artist + DELIMITER + album + DELIMITER + lyric + DELIMITER + "\n";
	}
}
