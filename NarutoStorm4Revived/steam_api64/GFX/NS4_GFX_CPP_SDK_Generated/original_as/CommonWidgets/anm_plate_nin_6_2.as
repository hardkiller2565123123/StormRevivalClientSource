package shop_catalog_fla
{
   import adobe.utils.*;
   import flash.accessibility.*;
   import flash.desktop.*;
   import flash.display.*;
   import flash.errors.*;
   import flash.events.*;
   import flash.external.*;
   import flash.filters.*;
   import flash.geom.*;
   import flash.globalization.*;
   import flash.media.*;
   import flash.net.*;
   import flash.net.drm.*;
   import flash.printing.*;
   import flash.profiler.*;
   import flash.sampler.*;
   import flash.sensors.*;
   import flash.system.*;
   import flash.text.*;
   import flash.text.engine.*;
   import flash.text.ime.*;
   import flash.ui.*;
   import flash.utils.*;
   import flash.xml.*;
   import script.icon_checkbox.nut_checkbox;
   import script.icon_new.nut_new;
   import script.icon_rarity.nut_rarity;
   import script.shop_cmn.nut_blank;
   import script.shop_cmn.nut_sold;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_line;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public dynamic class anm_plate_nin_6 extends MovieClip
   {
      
      public var all_line:nut_line;
      
      public var dmy_image:nut_tex00;
      
      public var mc_blank:nut_blank;
      
      public var mc_check:nut_checkbox;
      
      public var mc_new:nut_new;
      
      public var mc_nin_price:MovieClip;
      
      public var mc_rarity:nut_rarity;
      
      public var mc_sold:nut_sold;
      
      public var txt_nin_num:smb_font;
      
      public function anm_plate_nin_6()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4,4,this.frame5,5,this.frame6,6,this.frame7,7,this.frame8,8,this.frame9);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_nin_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_nin_num.SetTextSize(28);
         this.mc_nin_price.txt_nin_price.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.mc_nin_price.txt_nin_price.SetTextSize(30);
         this.txt_nin_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.mc_nin_price.txt_nin_price.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame2() : *
      {
         this.txt_nin_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.mc_nin_price.txt_nin_price.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame3() : *
      {
         this.txt_nin_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.mc_nin_price.txt_nin_price.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame4() : *
      {
         this.txt_nin_num.SetTextColor(6970438);
         this.mc_nin_price.txt_nin_price.SetTextColor(6970438);
      }
      
      internal function frame5() : *
      {
         this.txt_nin_num.SetTextColor(6970438);
         this.mc_nin_price.txt_nin_price.SetTextColor(6970438);
      }
      
      internal function frame6() : *
      {
         this.txt_nin_num.SetTextColor(6970438);
         this.mc_nin_price.txt_nin_price.SetTextColor(6970438);
      }
      
      internal function frame7() : *
      {
         this.txt_nin_num.SetTextColor(6970438);
         this.mc_nin_price.txt_nin_price.SetTextColor(6970438);
      }
      
      internal function frame8() : *
      {
         this.txt_nin_num.SetTextColor(4920576);
         this.mc_nin_price.txt_nin_price.SetTextColor(4920576);
      }
      
      internal function frame9() : *
      {
         this.txt_nin_num.SetTextColor(4920576);
         this.mc_nin_price.txt_nin_price.SetTextColor(4920576);
      }
   }
}

