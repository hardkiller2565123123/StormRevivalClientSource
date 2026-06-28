package result_main_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol128")]
   public dynamic class anm_rank_msg_22 extends MovieClip
   {
      
      public var txt_msg:smb_font;
      
      public function anm_rank_msg_22()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_msg.SetText("今回のバトル評価_gy");
         this.txt_msg.SetTextSize(28);
         this.txt_msg.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_msg.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_msg.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_msg.SetTextFieldWidth(670);
         this.txt_msg.SetTextFit(true);
      }
   }
}

