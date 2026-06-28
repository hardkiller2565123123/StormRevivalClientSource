package script.custom
{
   import ELoader.ExtendLoader;
   import Language.LanguageKeyCode;
   import flash.display.DisplayObject;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   import script.icon_new.nut_none_l;
   import script.infoData.OugiFinInfoData;
   import script.infoData.OugiFinInfoDataManager;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base7;
   import script.xcmn_tex00.nut_tex00;
   import script.xcmn_unset.smb_base;
   import script.xcp_frame_c1.smb_frame_c1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol18")]
   public class nut_ougifin extends MovieClip
   {
      
      public var dmy_icon_l:nut_tex00;
      
      public var mc_blank_txt:MovieClip;
      
      public var mc_icon_set00:smb_ougifin_sel;
      
      public var mc_icon_set01:smb_ougifin_sel;
      
      public var mc_icon_set02:smb_ougifin_sel;
      
      public var mc_icon_set03:smb_ougifin_sel;
      
      public var mc_item_name2:MovieClip;
      
      public var mc_none_l:nut_none_l;
      
      public var mc_off:MovieClip;
      
      public var mc_ougifin_base:nut_base7;
      
      public var mc_ougifin_frame:smb_frame_c1;
      
      public var mc_txt_base:smb_base;
      
      private var m_itemNameTextMC:smb_font;
      
      private var m_selItemMCList:Array;
      
      private var m_noneIconMC:MovieClip;
      
      private var m_dmyIconMC:MovieClip;
      
      private var m_loaderList:Array;
      
      private var m_selIdx:int = -1;
      
      private var m_decideIdx:int = -1;
      
      private var m_loadImgIdx:int = -1;
      
      private var m_isRTL:Boolean = false;
      
      private var m_infoDataMng:OugiFinInfoDataManager;
      
      public function nut_ougifin()
      {
         var _loc3_:String = null;
         var _loc4_:smb_ougifin_sel = null;
         super();
         addFrameScript(3,this.frame4,6,this.frame7,9,this.frame10,12,this.frame13);
         stop();
         this.m_noneIconMC = this["mc_none_l"];
         this.m_dmyIconMC = this["dmy_icon_l"];
         this.m_itemNameTextMC = this["mc_item_name2"]["txt_item_name2"];
         var _loc1_:int = 0;
         this.m_loaderList = new Array(define.OUGIFIN_SEL_ICON_NUM);
         this.m_selItemMCList = new Array(define.OUGIFIN_SEL_ICON_NUM);
         _loc1_ = 0;
         while(_loc1_ < define.OUGIFIN_SEL_ICON_NUM)
         {
            _loc3_ = "mc_icon_set0" + _loc1_;
            _loc4_ = this[_loc3_];
            this.m_selItemMCList[_loc1_] = _loc4_;
            _loc4_.SetEnable();
            _loc4_.SetNewIcon(false);
            _loc4_.SetConfirmIcon(false);
            _loc4_.SetIndexNumber(_loc1_ + 1);
            this.m_loaderList[_loc1_] = new ExtendLoader();
            this.m_dmyIconMC.addChild(this.m_loaderList[_loc1_]);
            _loc1_++;
         }
         this.m_noneIconMC.visible = false;
         var _loc2_:LanguageKeyCode = new LanguageKeyCode();
         if(_loc2_.GetGameSetLang() == _loc2_.GetArabicKeyCode())
         {
            this.m_isRTL = true;
         }
         else
         {
            this.m_isRTL = false;
         }
      }
      
      public function Initialize(param1:OugiFinInfoDataManager) : *
      {
         var _loc3_:OugiFinInfoData = null;
         var _loc4_:smb_ougifin_sel = null;
         var _loc5_:ExtendLoader = null;
         var _loc6_:String = null;
         var _loc7_:URLRequest = null;
         this.m_infoDataMng = param1;
         var _loc2_:int = 0;
         while(_loc2_ < define.OUGIFIN_SEL_ICON_NUM)
         {
            _loc3_ = param1.GetData(_loc2_);
            _loc4_ = this.m_selItemMCList[_loc2_];
            if(_loc3_.m_isEnable)
            {
               _loc4_.SetEnable();
            }
            else
            {
               _loc4_.SetDisable();
            }
            _loc4_.SetNewIcon(_loc3_.m_isNew);
            _loc5_ = this.m_loaderList[_loc2_];
            _loc6_ = define.GetOugiFinishFilePath(_loc3_.m_imgFileName);
            _loc7_ = new URLRequest(_loc6_);
            _loc5_.unload();
            _loc5_.load(_loc7_);
            _loc5_.contentLoaderInfo.addEventListener(Event.COMPLETE,this.ImgLoaded(_loc2_));
            _loc2_++;
         }
         this.SetDispItemName(this.m_selIdx);
      }
      
      public function SetupFirst(param1:int) : *
      {
         var _loc4_:smb_ougifin_sel = null;
         var _loc2_:int = 0;
         while(_loc2_ < define.OUGIFIN_SEL_ICON_NUM)
         {
            _loc4_ = this.m_selItemMCList[_loc2_];
            if(param1 == _loc2_)
            {
               _loc4_.SetConfirmIcon(true);
            }
            else
            {
               _loc4_.SetConfirmIcon(false);
            }
            _loc2_++;
         }
         this.m_decideIdx = param1;
         var _loc3_:OugiFinInfoData = this.m_infoDataMng.GetData(this.m_decideIdx);
         this.SetImg(_loc3_.m_imgFileName,this.m_decideIdx);
      }
      
      public function Open(param1:Boolean) : *
      {
         if(param1)
         {
            this.gotoAndStop("on");
         }
         else
         {
            this.gotoAndPlay("in");
         }
      }
      
      public function Close(param1:Boolean) : *
      {
         if(param1)
         {
            this.gotoAndPlay("end");
         }
         else
         {
            this.gotoAndPlay("out");
         }
      }
      
      public function Active() : *
      {
         this.gotoAndPlay("loop");
      }
      
      public function Decide() : Boolean
      {
         if(this.m_decideIdx == this.m_selIdx)
         {
            return false;
         }
         var _loc1_:OugiFinInfoData = this.m_infoDataMng.GetData(this.m_selIdx);
         if(_loc1_.m_isEnable == false)
         {
            return false;
         }
         var _loc2_:smb_ougifin_sel = this.m_selItemMCList[this.m_decideIdx];
         _loc2_.SetConfirmIcon(false);
         _loc2_ = this.m_selItemMCList[this.m_selIdx];
         _loc2_.SetConfirmIcon(true);
         this.m_decideIdx = this.m_selIdx;
         this.NewIconOff(this.m_selIdx);
         return true;
      }
      
      public function IsEnableOugiFinishPlay() : Boolean
      {
         var _loc1_:OugiFinInfoData = this.m_infoDataMng.GetData(this.m_selIdx);
         if(_loc1_.m_isEnable == false)
         {
            return false;
         }
         return true;
      }
      
      private function SetDispItemName(param1:int) : *
      {
         var _loc3_:OugiFinInfoData = null;
         var _loc2_:String = "";
         if(param1 >= 0 && param1 < define.OUGIFIN_SEL_ICON_NUM)
         {
            _loc3_ = this.m_infoDataMng.GetData(param1);
            _loc2_ = _loc3_.m_msgId;
         }
         this.m_itemNameTextMC.SetTextFieldWidth(800);
         this.m_itemNameTextMC.SetTextWordWrap(true);
         this.m_itemNameTextMC.SetTextPivot(smb_font.CCD_PIVOT_CC);
         if(this.m_isRTL)
         {
            this.m_itemNameTextMC.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
         else
         {
            this.m_itemNameTextMC.SetTextAlign(smb_font.CCD_ALIGN_LEFT);
         }
         this.m_itemNameTextMC.SetText(_loc2_);
      }
      
      public function Update(param1:int) : *
      {
         if(param1 != this.m_selIdx)
         {
            this.NewIconOff(this.m_selIdx);
            this.SetIconEnable(this.m_selIdx);
            this.SetIconSelect(param1);
            this.m_selIdx = param1;
            this.SetDispItemName(this.m_selIdx);
         }
      }
      
      private function SetIconEnable(param1:int) : *
      {
         var _loc2_:smb_ougifin_sel = null;
         var _loc3_:OugiFinInfoData = null;
         if(param1 >= 0 && param1 < define.OUGIFIN_SEL_ICON_NUM)
         {
            _loc2_ = this.m_selItemMCList[param1];
            _loc3_ = this.m_infoDataMng.GetData(param1);
            if(_loc3_.m_isEnable)
            {
               _loc2_.SetEnable();
            }
            else
            {
               _loc2_.SetDisable();
            }
         }
      }
      
      private function SetIconSelect(param1:int) : *
      {
         var _loc2_:smb_ougifin_sel = null;
         var _loc3_:OugiFinInfoData = null;
         if(param1 >= 0 && param1 < define.OUGIFIN_SEL_ICON_NUM)
         {
            _loc2_ = this.m_selItemMCList[param1];
            _loc3_ = this.m_infoDataMng.GetData(param1);
            if(_loc3_.m_isEnable)
            {
               _loc2_.SetSelect();
            }
            else
            {
               _loc2_.SetSelect();
            }
            this.m_noneIconMC.visible = !_loc3_.m_isEnable;
            this.m_dmyIconMC.visible = _loc3_.m_isEnable;
            if(this.m_dmyIconMC.visible)
            {
               this.SetImg(_loc3_.m_imgFileName,param1);
            }
         }
      }
      
      private function SetImg(param1:String, param2:int) : *
      {
         var _loc4_:DisplayObject = null;
         var _loc3_:int = 0;
         while(_loc3_ < define.OUGIFIN_SEL_ICON_NUM)
         {
            _loc4_ = this.GetImgMC(_loc3_);
            if(_loc4_ != null)
            {
               _loc4_.visible = _loc3_ == param2;
            }
            _loc3_++;
         }
      }
      
      private function ImgLoaded(param1:int) : Function
      {
         var inIdx:int = param1;
         return function ImgLoadedCore(param1:Event):*
         {
            var _loc2_:* = GetImgMC(inIdx);
            if(_loc2_ != null)
            {
               _loc2_.x = -_loc2_.width / 2;
               _loc2_.y = -_loc2_.height / 2;
            }
         };
      }
      
      private function GetImgMC(param1:int) : DisplayObject
      {
         var _loc3_:ExtendLoader = null;
         var _loc2_:DisplayObject = null;
         if(param1 >= 0 && param1 < this.m_loaderList.length)
         {
            _loc3_ = this.m_loaderList[param1];
            _loc2_ = _loc3_.content;
         }
         return _loc2_;
      }
      
      private function NewIconOff(param1:int) : *
      {
         var _loc3_:smb_ougifin_sel = null;
         var _loc2_:OugiFinInfoData = this.m_infoDataMng.GetData(param1);
         if(_loc2_ != null && _loc2_.m_isNew)
         {
            _loc2_.m_isNew = false;
            _loc3_ = this.m_selItemMCList[param1];
            _loc3_.SetNewIcon(false);
         }
      }
      
      public function SetVisibleNoneIcon(param1:Boolean) : *
      {
         this.m_noneIconMC.visible = param1;
      }
      
      internal function frame4() : *
      {
         stop();
      }
      
      internal function frame7() : *
      {
         stop();
      }
      
      internal function frame10() : *
      {
         stop();
      }
      
      internal function frame13() : *
      {
         stop();
      }
   }
}

