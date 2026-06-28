package custom_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol17")]
   public dynamic class smb_mc_item_name2_11 extends MovieClip
   {
      
      public var txt_item_name2:smb_font;
      
      public function smb_mc_item_name2_11()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_item_name2.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_item_name2.SetTextSize(30);
      }
   }
}

