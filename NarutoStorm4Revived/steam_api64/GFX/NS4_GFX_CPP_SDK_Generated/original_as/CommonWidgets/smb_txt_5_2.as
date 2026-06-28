package cutin_msg_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public dynamic class smb_txt_5 extends MovieClip
   {
      
      public var txt_msg:smb_font;
      
      public function smb_txt_5()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_msg.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_msg.SetTextSize(60);
         this.txt_msg.SetTextRubyEnable(false);
      }
   }
}

