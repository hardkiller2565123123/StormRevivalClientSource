package num_time_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class smb_msg_8 extends MovieClip
   {
      
      public var txt_msg:smb_font;
      
      public function smb_msg_8()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_msg.SetTextSize(28);
         this.txt_msg.SetTextColor(16777164);
         this.txt_msg.SetTextPivot(smb_font.CCD_PIVOT_CC);
      }
   }
}

