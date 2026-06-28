package result_net_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class smb_bp_plate_12 extends MovieClip
   {
      
      public var txt_bp_head00:smb_font;
      
      public var txt_bp_head01:smb_font;
      
      public var txt_bp_num01:smb_font;
      
      public var txt_bp_num00:smb_font;
      
      public function smb_bp_plate_12()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_bp_head00.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_bp_head00.SetTextColor(15058221);
         this.txt_bp_head00.SetTextFieldWidth(1000);
         this.txt_bp_head00.SetTextFit(true);
         this.txt_bp_head01.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_bp_head01.SetTextFieldWidth(1000);
         this.txt_bp_head01.SetTextFit(true);
         this.txt_bp_num00.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_bp_num00.SetTextColor(15058221);
         this.txt_bp_num01.SetTextPivot(smb_font.CCD_PIVOT_CC);
      }
   }
}

