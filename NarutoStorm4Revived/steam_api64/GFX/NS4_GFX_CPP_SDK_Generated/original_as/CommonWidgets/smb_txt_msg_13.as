package hist_cmn_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol41")]
   public dynamic class smb_txt_msg_13 extends MovieClip
   {
      
      public var txt_msg:smb_font;
      
      public function smb_txt_msg_13()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_msg.SetTextSize(30);
         this.txt_msg.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_msg.SetTextFieldWidth(597);
         this.txt_msg.SetTextScroll(true);
         this.txt_msg.SetTextColor(16777215);
         this.txt_msg.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_msg.StopTextScroll();
      }
      
      internal function frame2() : *
      {
         this.txt_msg.SetDropShadowFilter(16771214);
         this.txt_msg.SetTextColor(8653824);
         this.txt_msg.PlayTextScroll();
      }
      
      internal function frame3() : *
      {
         this.stop();
         this.txt_msg.DisableDropShadowFilter();
         this.txt_msg.SetTextColor(921102);
         this.txt_msg.StopTextScroll();
      }
   }
}

