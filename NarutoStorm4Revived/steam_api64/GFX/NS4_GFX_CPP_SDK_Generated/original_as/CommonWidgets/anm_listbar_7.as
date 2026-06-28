package net_seach_fla
{
   import flash.display.MovieClip;
   import script.net_icon.nut_info;
   import script.net_icon.nut_type;
   import script.xcmn_font.smb_font;
   import script.xcmn_net.nut_icon_wave;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol14")]
   public dynamic class anm_listbar_7 extends MovieClip
   {
      
      public var all_icon_wave:nut_icon_wave;
      
      public var all_info:nut_info;
      
      public var all_side:nut_info;
      
      public var all_stage:nut_info;
      
      public var all_status:nut_type;
      
      public var all_type:nut_info;
      
      public var txt_match:smb_font;
      
      public var txt_useid:smb_font;
      
      public function anm_listbar_7()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_useid.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_useid.SetTextColor(9906944);
         this.txt_useid.SetTextFieldWidth(460);
         this.txt_useid.SetTextFit(true);
         this.txt_match.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_match.SetTextColor(9906944);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_useid.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_useid.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_useid.SetTextFieldWidth(480);
         this.txt_useid.SetTextFit(true);
         this.txt_match.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_match.SetTextColor(smb_font.CCD_COLOR_WHITE);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_useid.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_useid.SetTextColor(9906944);
         this.txt_useid.SetTextFieldWidth(530);
         this.txt_useid.SetTextFit(true);
      }
      
      internal function frame4() : *
      {
         stop();
         this.txt_useid.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_useid.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_useid.SetTextFieldWidth(530);
         this.txt_useid.SetTextFit(true);
      }
   }
}

