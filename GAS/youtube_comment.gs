function youtubeCommentFetcher() {
  var SS = SpreadsheetApp.getActiveSpreadsheet();
  // video_list��VID(YouTube�����ID)����͂��Ă�������
  // ex. "l9F1J0DGFg0", 'J9IDKbPbQVY'
  var video_list   = [
    'i_tyFCG-fEk'
  ];
  
  // =================�������牺�͏��������Ȃ�=================
  for (var v = 0; v < video_list.length; v++) {
    var video_id  = video_list[v];
    var video = YouTube.Videos.list('id,snippet, statistics', {
      id: video_id,
    });
    
    if (v == 0) {
      var sheet = SS.getActiveSheet();
    } else {
      var sheet = SS.insertSheet();
    }
    sheet.setName(video.items[0].snippet.title);
    
    var row          = 2;
    var col          = 1;
    sheet.getRange(1, 1).setValue("�r�f�I��");
    sheet.getRange(1, 2).setValue("�`�����l����");
    sheet.getRange(1, 3).setValue("�R�����g���[�U�[��");
    sheet.getRange(1, 4).setValue("�R�����g��");
    sheet.getRange(1, 5).setValue("�R�����g");

    

    var PageToken = ''
    
    while (true) {
      var comment_list = YouTube.CommentThreads.list('id, replies, snippet', {
        videoId: video_id,
        maxResults: 100,
        pageToken: PageToken,
      });
    
      for (var i = 0; i < comment_list.items.length; i++) {
        sheet.getRange(row, col).setValue(video.items[0].snippet.title);
        sheet.getRange(row, col + 1).setValue(video.items[0].snippet.channelTitle);
        sheet.getRange(row, col + 2).setValue(comment_list.items[i].snippet.topLevelComment.snippet.authorDisplayName);
        sheet.getRange(row, col + 3).setValue(comment_list.items[i].snippet.topLevelComment.snippet.publishedAt);
        sheet.getRange(row, col + 4).setValue(comment_list.items[i].snippet.topLevelComment.snippet.textDisplay);
        row += 1;
        if (typeof comment_list.items[i].replies !== "undefined") {
           for (var r = 0; r < comment_list.items[i].replies.comments.length; r++) {             
             sheet.getRange(row, col).setValue(video.items[0].snippet.title);
             sheet.getRange(row, col + 1).setValue(video.items[0].snippet.channelTitle);
             sheet.getRange(row, col + 2).setValue(comment_list.items[i].replies.comments[r].snippet.authorDisplayName);
             sheet.getRange(row, col + 3).setValue(comment_list.items[i].replies.comments[r].snippet.publishedAt);
             sheet.getRange(row, col + 4).setValue(comment_list.items[i].replies.comments[r].snippet.textDisplay);
             row += 1;
           }
         }
      }
      PageToken = comment_list.nextPageToken
      if (typeof PageToken == "undefined") {
        break
      }
    }
  }
}
