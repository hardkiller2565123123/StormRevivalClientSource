package hist_cmn_fla
{
   import flash.display.MovieClip;
   import script.icon_checkbox.nut_checkbox;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_line;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol29")]
   public dynamic class anm_bonus_68 extends MovieClip
   {
      
      public var all_checkbox:nut_checkbox;
      
      public var all_line:nut_line;
      
      public var dmy_item:nut_tex00;
      
      public var txt_cond:smb_font;
      
      public var txt_item:smb_font;
      
      public var txt_num:smb_font;
      
      public function anm_bonus_68()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_cond.SetText("1. Achever l\'ennemi avec une Technique secrète assistée.＊＊＊＊＊＊＊＊＊");
         this.txt_item.SetText("白金のクナイABCgy_123:!?　＊＊＊＊＊＊＊＊＊＊＊＊＊＊");
         this.txt_num.SetText("×99");
         this.txt_cond.SetTextSize(28);
         this.txt_cond.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cond.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_cond.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_cond.SetTextFieldWidth(920);
         this.txt_cond.SetTextFit(true);
         this.txt_item.SetTextSize(30);
         this.txt_item.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_item.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_item.SetTextFieldWidth(766);
         this.txt_item.SetTextFit(true);
         this.txt_num.SetTextSize(33);
         this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_num.SetTextFieldWidth(84);
         this.txt_num.SetTextFit(true);
      }
   }
}

