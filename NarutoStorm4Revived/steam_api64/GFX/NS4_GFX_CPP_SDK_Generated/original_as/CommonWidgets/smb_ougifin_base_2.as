package script.custom
{
   import ELoader.ExtendLoader;
   import flash.display.DisplayObject;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   import script.icon_new.nut_none;
   import script.xcmn_menu.nut_frame_1;
   import script.xcmn_menu.nut_frame_2;
   import script.xcmn_tex00.nut_tex00;
   import script.xcp_frame_c1.smb_frame_c2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol20")]
   public class smb_ougifin_base extends MovieClip
   {
      
      public var dmy_thumb:nut_tex00;
      
      public var mc_frame:smb_frame_c2;
      
      public var mc_none:nut_none;
      
      public var mc_ougifin_base:MovieClip;
      
      public var mc_ougifin_edit:nut_frame_2;
      
      public var mc_ougifin_off:MovieClip;
      
      public var mc_ougifin_sel:nut_frame_1;
      
      internal var m_noneIconMC:MovieClip;
      
      internal var m_dmyIconMC:MovieClip;
      
      internal var m_loaderList:Array;
      
      internal var m_loadFilePath:String = null;
      
      internal var m_loadInstName:String = null;
      
      internal var m_imgIdx:int = 0;
      
      public function smb_ougifin_base()
      {
         super();
         addFrameScript(0,this.frame1);
         stop();
         this.m_noneIconMC = this["mc_none"];
         this.m_dmyIconMC = this["dmy_thumb"];
         this.m_noneIconMC.visible = false;
         this.m_loaderList = new Array(define.OUGIFIN_SEL_ICON_NUM);
         var _loc1_:int = 0;
         while(_loc1_ < define.OUGIFIN_SEL_ICON_NUM)
         {
            this.m_loaderList[_loc1_] = new ExtendLoader();
            this.m_dmyIconMC.addChild(this.m_loaderList[_loc1_]);
            _loc1_++;
         }
         this.m_imgIdx = 0;
      }
      
      public function LoadImgAll(param1:Array) : *
      {
         var _loc4_:ExtendLoader = null;
         var _loc5_:String = null;
         var _loc6_:URLRequest = null;
         var _loc2_:int = int(param1.length);
         var _loc3_:int = 0;
         while(_loc3_ < _loc2_)
         {
            _loc4_ = this.m_loaderList[_loc3_];
            _loc5_ = define.GetOugiFinishFilePath(param1[_loc3_]);
            _loc6_ = new URLRequest(_loc5_);
            _loc4_.unload();
            _loc4_.load(_loc6_);
            this.m_dmyIconMC.visible = false;
            _loc4_.contentLoaderInfo.addEventListener(Event.COMPLETE,this.ImgLoaded(_loc3_));
            _loc3_++;
         }
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
      
      public function SetSelect() : *
      {
         this.gotoAndStop("on");
      }
      
      public function SetDisable() : *
      {
         this.gotoAndStop("off");
      }
      
      public function SetEnable() : *
      {
         this.gotoAndStop("normal");
      }
      
      public function SetImpossible() : *
      {
         this.gotoAndStop("impos");
      }
      
      public function SetImg(param1:int) : *
      {
         var _loc2_:int = 0;
         while(_loc2_ < define.OUGIFIN_SEL_ICON_NUM)
         {
            this.m_loaderList[_loc2_].visible = false;
            _loc2_++;
         }
         this.m_imgIdx = param1;
         this.m_loaderList[this.m_imgIdx].visible = true;
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
               m_dmyIconMC.visible = true;
            }
            var _loc3_:* = 0;
            while(_loc3_ < define.OUGIFIN_SEL_ICON_NUM)
            {
               m_loaderList[_loc3_].visible = false;
               _loc3_++;
            }
            m_loaderList[m_imgIdx].visible = true;
         };
      }
      
      internal function frame1() : *
      {
         stop();
      }
   }
}

