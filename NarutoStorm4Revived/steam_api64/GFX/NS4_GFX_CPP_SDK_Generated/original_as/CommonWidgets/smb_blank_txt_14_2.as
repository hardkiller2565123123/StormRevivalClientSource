package custom_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public dynamic class smb_blank_txt_14 extends MovieClip
   {
      
      public var txt_blank:smb_font;
      
      public function smb_blank_txt_14()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_blank.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_blank.SetTextColor(4737096);
         this.txt_blank.SetTextSize(33);
         this.txt_blank.visible = false;
      }
   }
}

