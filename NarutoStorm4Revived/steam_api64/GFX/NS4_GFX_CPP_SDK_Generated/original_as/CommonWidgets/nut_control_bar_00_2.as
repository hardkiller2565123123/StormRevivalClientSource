package script.option_keyboard
{
   import flash.display.MovieClip;
   import script.msg_match_s_txt.all_nut;
   import script.xcmn_btn_plat.all_btn_plat;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_cursor_m;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol13")]
   public dynamic class nut_control_bar_00 extends MovieClip
   {
      
      public var mc_player1:script.msg_match_s_txt.all_nut;
      
      public var mc_control_arrow01_l:nut_cursor_m;
      
      public var mc_player2:script.msg_match_s_txt.all_nut;
      
      public var mc_control_arrow01_r:nut_cursor_m;
      
      public var mc_control_arrow02_l:nut_cursor_m;
      
      public var mc_control_arrow02_r:nut_cursor_m;
      
      public var mc_xbtn02:all_btn_plat;
      
      public var txt_control_title:smb_font;
      
      public var mc_xbtn01:all_btn_plat;
      
      public var txt_select01:smb_font;
      
      public var mc_select_frame_01:MovieClip;
      
      public var txt_select02:smb_font;
      
      public var mc_select_frame_02:MovieClip;
      
      public function nut_control_bar_00()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_select01.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select01.SetTextColor(11606272);
         this.txt_select01.SetDropShadowFilter(11645361);
         this.txt_select01.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
         this.txt_control_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_control_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_control_title.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
         this.txt_select02.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select02.SetTextColor(11606272);
         this.txt_select02.SetDropShadowFilter(11645361);
         this.txt_select02.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_select01.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select01.SetTextColor(16777215);
         this.txt_select01.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_select01.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
         this.txt_control_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_control_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_control_title.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
         this.txt_select02.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select02.SetTextColor(16777215);
         this.txt_select02.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_select02.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_select01.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select01.SetTextColor(11606272);
         this.txt_select01.SetDropShadowFilter(11645361);
         this.txt_select01.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
         this.txt_control_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_control_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_control_title.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
         this.txt_select02.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select02.SetTextColor(16777215);
         this.txt_select02.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_select02.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
      }
      
      internal function frame4() : *
      {
         stop();
         this.txt_select01.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select01.SetTextColor(16777215);
         this.txt_select01.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_select01.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
         this.txt_control_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_control_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_control_title.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
         this.txt_select02.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select02.SetTextColor(11606272);
         this.txt_select02.SetDropShadowFilter(11645361);
         this.txt_select02.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
      }
   }
}

