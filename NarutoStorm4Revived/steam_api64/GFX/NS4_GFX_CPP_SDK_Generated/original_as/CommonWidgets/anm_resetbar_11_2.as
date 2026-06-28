package option_fla
{
   import flash.display.MovieClip;
   import script.msg_match_s_txt.all_nut;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base4;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol30")]
   public dynamic class anm_resetbar_11 extends MovieClip
   {
      
      public var all_base4:nut_base4;
      
      public var mc_player1:all_nut;
      
      public var mc_player2:all_nut;
      
      public var txt_control_title:smb_font;
      
      public function anm_resetbar_11()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_control_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_control_title.SetTextColor(11606272);
         this.txt_control_title.SetDropShadowFilter(11645361);
         this.txt_control_title.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_control_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_control_title.SetTextColor(16777215);
         this.txt_control_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_control_title.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
      }
   }
}

