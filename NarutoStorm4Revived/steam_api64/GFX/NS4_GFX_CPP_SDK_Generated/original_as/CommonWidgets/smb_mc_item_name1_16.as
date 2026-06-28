package custom_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public dynamic class smb_mc_item_name1_16 extends MovieClip
   {
      
      public var txt_item_name1:smb_font;
      
      public function smb_mc_item_name1_16()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_item_name1.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_item_name1.SetTextSize(30);
      }
   }
}

