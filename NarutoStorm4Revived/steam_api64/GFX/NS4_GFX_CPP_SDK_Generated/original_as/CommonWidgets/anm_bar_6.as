package net_rank_fla
{
   import flash.display.MovieClip;
   import script.net_cmn.anm_msg;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class anm_bar_6 extends MovieClip
   {
      
      public var all_myrank:anm_msg;
      
      public var txt_bp_num:smb_font;
      
      public var txt_per_num:smb_font;
      
      public var txt_rank_num:smb_font;
      
      public var txt_ranking_num:smb_font;
      
      public var txt_title:smb_font;
      
      public var txt_userid:smb_font;
      
      public var txt_wins_num:smb_font;
      
      public function anm_bar_6()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4,4,this.frame5,5,this.frame6);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_ranking_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_ranking_num.SetTextColor(16774492);
         this.txt_ranking_num.SetDropShadowFilter(6358853);
         this.txt_ranking_num.SetTextFieldWidth(166);
         this.txt_userid.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_userid.SetTextSize(29);
         this.txt_userid.SetTextColor(16774492);
         this.txt_userid.SetDropShadowFilter(6358853);
         this.txt_bp_num.SetTextColor(16774492);
         this.txt_bp_num.SetDropShadowFilter(6358853);
         this.txt_bp_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_bp_num.SetTextFieldWidth(260);
         this.txt_bp_num.SetTextFit(true);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_ranking_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_ranking_num.SetTextColor(16774492);
         this.txt_ranking_num.SetDropShadowFilter(6358853);
         this.txt_ranking_num.SetTextFieldWidth(166);
         this.txt_userid.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_userid.SetTextSize(29);
         this.txt_userid.SetTextColor(16774492);
         this.txt_userid.SetDropShadowFilter(6358853);
         this.txt_wins_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_wins_num.SetTextSize(25);
         this.txt_wins_num.SetTextColor(16774492);
         this.txt_wins_num.SetDropShadowFilter(6358853);
         this.txt_wins_num.SetTextFieldWidth(260);
         this.txt_wins_num.SetTextFit(true);
         this.txt_per_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_per_num.SetTextColor(16774492);
         this.txt_per_num.SetTextSize(25);
         this.txt_per_num.SetDropShadowFilter(6358853);
         this.txt_per_num.SetTextFieldWidth(260);
         this.txt_per_num.SetTextFit(true);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_ranking_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_ranking_num.SetTextColor(16774492);
         this.txt_ranking_num.SetDropShadowFilter(6358853);
         this.txt_ranking_num.SetTextFieldWidth(166);
         this.txt_userid.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_userid.SetTextSize(29);
         this.txt_userid.SetTextColor(16774492);
         this.txt_userid.SetDropShadowFilter(6358853);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextSize(25);
         this.txt_title.SetTextColor(16774492);
         this.txt_title.SetDropShadowFilter(6358853);
         this.txt_title.SetTextFieldWidth(260);
         this.txt_title.SetTextFit(true);
         this.txt_rank_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_rank_num.SetTextSize(25);
         this.txt_rank_num.SetTextColor(16774492);
         this.txt_rank_num.SetDropShadowFilter(6358853);
         this.txt_rank_num.SetTextFieldWidth(260);
         this.txt_rank_num.SetTextFit(true);
      }
      
      internal function frame4() : *
      {
         stop();
         this.txt_ranking_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_ranking_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_ranking_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_ranking_num.SetTextFieldWidth(166);
         this.txt_userid.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_userid.SetTextSize(29);
         this.txt_userid.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_userid.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_bp_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_bp_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_bp_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_bp_num.SetTextFieldWidth(260);
         this.txt_bp_num.SetTextFit(true);
      }
      
      internal function frame5() : *
      {
         stop();
         this.txt_ranking_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_ranking_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_ranking_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_ranking_num.SetTextFieldWidth(166);
         this.txt_userid.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_userid.SetTextSize(29);
         this.txt_userid.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_userid.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_wins_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_wins_num.SetTextSize(25);
         this.txt_wins_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_wins_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_wins_num.SetTextFieldWidth(260);
         this.txt_wins_num.SetTextFit(true);
         this.txt_per_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_per_num.SetTextSize(25);
         this.txt_per_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_per_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_per_num.SetTextFieldWidth(260);
         this.txt_per_num.SetTextFit(true);
      }
      
      internal function frame6() : *
      {
         stop();
         this.txt_ranking_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_ranking_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_ranking_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_ranking_num.SetTextFieldWidth(166);
         this.txt_userid.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_userid.SetTextSize(29);
         this.txt_userid.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_userid.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextSize(25);
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextFieldWidth(260);
         this.txt_title.SetTextFit(true);
         this.txt_rank_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_rank_num.SetTextSize(25);
         this.txt_rank_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_rank_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_rank_num.SetTextFieldWidth(260);
         this.txt_rank_num.SetTextFit(true);
      }
   }
}

